// Copyright (c) 2021, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// log_manager.cpp :
//
#include "log_manager.h"

#include <errno.h>
json_pathjson_path#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <array>
#include <filesystem>
#include <regex>

#include "app_logs.h"
#include "cal_data_upload.h"
#include "common.h"
#include "disk_info.h"
#include "narchive.h"
#include "ndlb.h"
#include "nfs_ext.h"
#include "traffic_info.h"
#include "audit_log.h"

namespace log_manager {

static constexpr const char* kFolderNameRegexStr = "^boot[0-9]{8}";
static constexpr const char* kDlbFolderDir = "/nio/log_manager";
static constexpr const char* kPackageJson = "/etc/log_manager.json";
static constexpr const char* kLatestPath = "/nio/logs/latest";

static constexpr const char* kDlbType = "log_manager";
static constexpr const char* kAppName = "log_manager_app";
static constexpr const char* kUpLoadFlagFile = "upload_done";
static constexpr const char* kCompressFlagFile = "compress_done";
static constexpr int kUuidMaxLength = 64;
static constexpr int kUploadDirMaxFolder = 50;
static constexpr int kPriority = 100;
static constexpr int64_t kUnitMB = 1024 * 1024;
static constexpr int64_t kDefaultSplitMaxSize = 1 * kUnitMB;
static constexpr int64_t kDefaultPackageMaxSize = 100 * kUnitMB;

namespace fs = std::filesystem;

LogManager::LogManager() {}

LogManager::~LogManager() {}

int LogManager::Start() {
  NLOG_INFO("Start log manaer");
  // This process must be run first to create folder
  // for new cycle
  log_root_dir_ = log_tool_.GetLogRootDir();
  CreateSymlink();

  startup_key_info_thread_ =
      std::thread(&LogManager::RecordStartUpKeyInfo, this);
  copy_syslog_ = std::thread(&LogManager::CopySyslogRealtime, this);
  package_thread_ = std::thread(&LogManager::PackageThread, this);
  app_logs_.Start();
  audit_log_.Start();
  return 0;
}

void LogManager::Stop() {
  if (startup_key_info_thread_.joinable()) {
    startup_key_info_thread_.join();
  }
  if (package_thread_.joinable()) {
    package_thread_.join();
  }
  if (copy_syslog_.joinable()) {
    copy_syslog_.join();
  }
  app_logs_.Stop();
  audit_log_.Stop();
  NLOG_INFO("Exit log manager");
  return;
}

void LogManager::PackageThread() {
  PackageParaInit();
  ReadPackagePara(kPackageJson);
  // Do not delete this sleep_for! Workaround for compress stuck in
  // archive_write_close. https://jira.nioint.com/browse/TOP-4569
  std::this_thread::sleep_for(std::chrono::seconds(10));
  if (CompressLog()) {
    NLOG_ERROR("Compress folders fail, stop dlb process!");
    return;
  }
  if (UploadLog()) {
    NLOG_ERROR("Upload log fail, stop dlb process!");
    return;
  }
}

int LogManager::CompressLog() {
  NLOG_INFO("Start compress folder");
  std::list<std::string> dlb_folder_list =
      nlog::FolderScan(kDlbFolderDir, kFolderNameRegexStr, CATCH_FOLDER);
  FolderNumControl(dlb_folder_list, kUploadDirMaxFolder);

  fs::path log_dir_base = fs::path(log_root_dir_).parent_path();
  std::list<std::string> folder_list = nlog::FolderScan(
      log_dir_base.string(), kFolderNameRegexStr, CATCH_FOLDER);
  fs::path out_dir = kDlbFolderDir;
  if (!folder_list.empty()) {
    folder_list.pop_back();
  }
  for (auto& folder_fullpath : folder_list) {
    std::string folder_name = fs::path(folder_fullpath).filename();
    fs::path input_dir = log_dir_base / folder_name;
    std::string compress_flag_file = input_dir / kCompressFlagFile;
    if (fs::exists(compress_flag_file) == true) {
      continue;
    }
    std::error_code rc;
    std::string dlb_out_dir = out_dir / folder_name;
    if (fs::exists(dlb_out_dir)) {
      if (!fs::remove_all(dlb_out_dir, rc)) {
        NLOG_ERROR("Remove ({}) failed, err: {}", dlb_out_dir,
                   rc.message().c_str());
        return -1;
      } else {
        NLOG_INFO("Remove ({}) succeed", dlb_out_dir);
      }
    }
    auto file_path =
        log_tool_.PackageLogs(apps_list_, input_dir.string(), dlb_out_dir,
                              split_max_size_, package_max_size_);
    if (fs::exists(file_path) == false) {
      NLOG_ERROR("packageLogs ({}) error", file_path);
      continue;
    }
    if (nfs::FileSaveContents(compress_flag_file.c_str(), "")) {
      NLOG_ERROR("{} gen fail, stop compress process!", compress_flag_file);
      return -1;
    }
  }
  return 0;
}

int LogManager::UploadLog() {
  NLOG_INFO("Start upload folder by dlb");
  std::list<std::string> dlb_folder_list =
      nlog::FolderScan(kDlbFolderDir, kFolderNameRegexStr, CATCH_FOLDER);

  fs::path out_dir = kDlbFolderDir;
  for (auto& folder_fullpath : dlb_folder_list) {
    std::string folder_name = fs::path(folder_fullpath).filename();
    std::string dlb_out_dir = out_dir / folder_name;
    std::string upload_flag_file = out_dir / folder_name / kUpLoadFlagFile;
    if (fs::exists(upload_flag_file) == true) {
      continue;
    }
    ndlb::NDlb dlb;
    if (dlb.DlbInit(kDlbType, kAppName, dlb_out_dir, kPriority)) {
      NLOG_ERROR("dlb init failed! type: {} path: {}", kDlbType, dlb_out_dir);
      return -1;
    }
    NLOG_INFO("Start upload ({})", dlb_out_dir);
    if (dlb.DlbUpLoad()) {
      NLOG_ERROR("dlb upload failed! type: {} path: {}", kDlbType, dlb_out_dir);
      return -1;
    }
    NLOG_INFO("Upload finish ({})", dlb_out_dir);
    if (nfs::FileSaveContents(upload_flag_file.c_str(), "")) {
      NLOG_ERROR("{} gen fail, stop compress process!", upload_flag_file);
      return -1;
    }
  }
  NLOG_INFO("End upload folder by dlb");
  return 0;
}

void LogManager::CopySyslogRealtime() {
  NLOG_INFO("Start joining copy_syslog_thread");
  ClearLog("syslog");
  auto logger = nlog::NLog::Instance()->NewLogger("syslog", false, "",
                                                  nlog::RotateLevel::kP0);
  logger->set_pattern("%v");

  std::string command =
      "journalctl -b 0 -o short-iso-precise -f -n 10000 | grep -v "
      "hw_manager | grep -v 'pps pps0' 2>&1";
  if (RecordLog(logger, command) != 0) {
    NLOG_ERROR("Execute cmd {} error!", command);
  }
}

void LogManager::RecordStartUpKeyInfo() {
  CollectDiskInfo();
  CalDataToUpload();
  CollectTrafficInfo();
}

int LogManager::CreateSymlink() {
  if (fs::exists(kLatestPath) || fs::is_symlink(kLatestPath)) {
    NLOG_INFO("{} exists", kLatestPath);
    fs::remove(kLatestPath);
  }
  int ret;
  ret = symlink(log_root_dir_.c_str(), kLatestPath);
  if (ret != 0) {
    NLOG_ERROR("error code:{} reason:{}", errno, strerror(errno));
    logger_->flush();
    return -1;
  }
  return 0;
}

void LogManager::PackageParaInit() {
  apps_list_.clear();
  apps_list_.push_back("syslog");
  apps_list_.push_back("log-manager");
  split_max_size_ = kDefaultSplitMaxSize;
  package_max_size_ = kDefaultPackageMaxSize;
}

void LogManager::ReadPackagePara(const std::string& path) {
  std::string data = nfs::FileGetContents(path.c_str());
  if (data.empty()) {
    NLOG_ERROR("{} don't exists, use default para!", path);
    return;
  }
  rapidjson::Document document;
  if (document.Parse(data.c_str()).HasParseError()) {
    NLOG_ERROR("{} parse fail, use default para!", path);
    return;
  }

  if (document.HasMember("app_list")) {
    const rapidjson::Value& childValue = document["app_list"];
    apps_list_.clear();
    for (rapidjson::SizeType i = 0; i < childValue.Size(); ++i) {
      apps_list_.push_back(childValue[i].GetString());
    }
  }

  rapidjson::Value::ConstMemberIterator iter =
      document.FindMember("split_size");

  if (iter != document.MemberEnd()) {
    split_max_size_ = iter->value.GetInt() * kUnitMB;
  }

  iter = document.FindMember("package_max_size");
  if (iter != document.MemberEnd()) {
    package_max_size_ = iter->value.GetInt() * kUnitMB;
  }
}

void LogManager::FolderNumControl(const std::list<std::string>& folder_list,
                                  const int folder_keep_max) {
  auto folder_list_size = folder_list.size();
  if (folder_list_size != 0) {
    int delete_size = folder_list.size() - folder_keep_max;
    auto delete_folder = folder_list.begin();
    while (delete_size > 0) {
      delete_size--;
      fs::remove_all(*delete_folder);
      NLOG_INFO("Remove folder: {}", *delete_folder);
      delete_folder++;
    }
  }
}

}  // namespace log_manager
