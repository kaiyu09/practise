// Copyright (c) 2022, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// fault_check.cpp : [file description]
//
#include "fault_check.h"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <map>
#include <memory>

#include "common/diagnostic/fault/fault_fw_calibration.pb.h"
#include "niodds/messaging/node.h"
#include "niodds/messaging/qos.h"
#include "nlog.h"

namespace calibration {
using nio::ad::QoS;

static const std::string kNioParaDir = "/nio/parameters";
static const std::string kCamDir = kNioParaDir + "/camera";
static const std::string kLidarDir = kNioParaDir + "/lidar";


// 枚举 类型的 数据, 同类型的变量赋值只能是枚举内部类型的值
// 枚举 可以是负值 需要是整数
enum class FaultStatus {
  kDefault = -1,
  kNotExist = 0,
  kExist = 1,
};

struct FileFaultStatus {
  std::string filename;
  FaultStatus status;
  // FaultStatus status;  定义status为枚举类型的值, 那么status只能是 枚举定义的值里面的值.
};

// clang-format off
static std::map<std::string, FileFaultStatus> err_to_file_map = {
    {"FL_Camera_Calibration_File_NotExisted", {kCamDir + "/front_left/front_left.json",       FaultStatus::kDefault }},
    {"FN_Camera_Calibration_File_NotExisted", {kCamDir + "/front_narrow/front_narrow.json",   FaultStatus::kDefault }},
    {"FR_Camera_Calibration_File_NotExisted", {kCamDir + "/front_right/front_right.json",     FaultStatus::kDefault }},
    {"FW_Camera_Calibration_File_NotExisted", {kCamDir + "/front_wide/front_wide.json",       FaultStatus::kDefault }},
    {"RL_Camera_Calibration_File_NotExisted", {kCamDir + "/rear_left/rear_left.json",         FaultStatus::kDefault }},
    {"RN_Camera_Calibration_File_NotExisted", {kCamDir + "/rear_narrow/rear_narrow.json",     FaultStatus::kDefault }},
    {"RR_Camera_Calibration_File_NotExisted", {kCamDir + "/rear_right/rear_right.json",       FaultStatus::kDefault }},
    {"SVC_FRONT_Calibration_File_NotExisted", {kCamDir + "/svc_front/svc_front.json",         FaultStatus::kDefault }},
    {"SVC_LEFT_Calibration_File_NotExisted",  {kCamDir + "/svc_left/svc_left.json",           FaultStatus::kDefault }},
    {"SVC_REAR_Calibration_File_NotExisted",  {kCamDir + "/svc_rear/svc_rear.json",           FaultStatus::kDefault }},
    {"SVC_RIGHT_Calibration_File_NotExisted", {kCamDir + "/svc_right/svc_right.json",         FaultStatus::kDefault }},
    {"Windshield_Remap_FIle_NotExisted",      {kCamDir + "/front_wide/remap.npz",             FaultStatus::kDefault }},
    {"Lidar_Calibration_File_NotExisted",     {kLidarDir + "/lidar_front.json",               FaultStatus::kDefault }}};
// clang-format on

FaultCheck::FaultCheck() {
  need_publish_ = true;
  is_terminate_ = false;
}
FaultCheck::~FaultCheck() {}

void FaultCheck::Start() {
  is_terminate_ = false;
  th_file_check_ = std::thread(&FaultCheck::CheckCalibFileHandler, this);
}

void FaultCheck::Stop() {
  is_terminate_ = true;
  th_file_check_.join();
}

int ReflectionSetBoolValue(
    const std::shared_ptr<google::protobuf::Message> &message,
    const std::string &type, bool value) {
  const google::protobuf::Descriptor *descriptor = message->GetDescriptor();
  const google::protobuf::Reflection *reflection = message->GetReflection();

  auto field = descriptor->FindFieldByName(type);
  if (field == nullptr) {
    NLOG_ERROR("FindFieldByName({}) failed", type.c_str());
    return -1;
  }

  if (field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_BOOL) {
    NLOG_ERROR("Not support type({})", type.c_str());
    return -1;
  }

  reflection->SetBool(message.get(), field, value);
  return 0;
}

void FaultCheck::CheckCalibFileHandler() {

  std::string node_name{"fault_fw_calibration"};
  auto node = nio::ad::Node::CreateNode(node_name);
  auto qos_keep_last_one =
      QoS(QoS::KEEP_LAST, 1, QoS::RELIABLE, QoS::TRANSIENT_LOCAL);
  auto pub = node->CreatePublisher<nio::ad::messages::FWCalibrationFaultInfo>(
      "common/diagnostic/fault/fault_fw_calibration", qos_keep_last_one);

  auto msg = std::make_shared<nio::ad::messages::FWCalibrationFaultInfo>();
  bool is_file_not_exist = true;
  FaultStatus status_get = FaultStatus::kDefault;

  while (is_terminate_ == false) {
    for (auto &iter : err_to_file_map) {
      if (!std::filesystem::exists(iter.second.filename)) {
        is_file_not_exist = true;
        status_get = FaultStatus::kNotExist;
      } else {
        is_file_not_exist = false;
        status_get = FaultStatus::kExist;
      }

      if (iter.second.status != status_get) {
        ReflectionSetBoolValue(msg, iter.first, is_file_not_exist);
        NLOG_INFO("{} changed to :{}", iter.first, is_file_not_exist);
        iter.second.status = status_get;
        need_publish_ = true;
      }
    }

    if (need_publish_) {
      pub->Publish(msg);
      need_publish_ = false;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
  };
}
} // namespace calibration
