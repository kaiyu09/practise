// Copyright (c) 2021, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// log_manager.h :
//
#pragma once
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "app_logs.h"
#include "audit_log.h"
#include "common/dlb/dlb_file_upload.pb.h"
#include "common/dlb/dlb_file_upload_response.pb.h"
#include "niodds/application/application.h"
#include "nlog.h"
#include "nlog_tool.h"
namespace log_manager {

class LogManager {
 public:
  LogManager();
  ~LogManager();

  int Start();
  void Stop();

 private:
  void CopySyslogRealtime();
  void RecordStartUpKeyInfo();
  void PackageThread();
  int CreateSymlink();
  int CompressLog();
  int UploadLog();
  void ReadPackagePara(const std::string& path);
  void PackageParaInit();

  void FolderNumControl(const std::list<std::string>& folder_list,
                        const int folder_keep_max);
  nlog::NlogTool log_tool_;
  std::vector<std::string> apps_list_;
  int64_t split_max_size_;
  int64_t package_max_size_;
  std::shared_ptr<spdlog::logger> logger_;
  std::string log_root_dir_ = "";
  std::string dlb_out_dir_ = "";

  std::thread copy_syslog_;
  std::thread package_thread_;
  std::thread startup_key_info_thread_;
  AppLogs app_logs_;
  AuditLog audit_log_;
};

}  // namespace log_manager
