// Copyright (c) 2022, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// json_file_deal.cpp : [file description]
//

#include <errno.h>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <thread>
#include <vector>

static const std::string json_path = "/home/nio/kkrepo/file/log_manager.json";
void ReadPackagePara(const std::string& path);

void ReadPackagePara(const std::string& path) {
  printf("rurnurnrurn");
  std::string data = nfs::FileGetContents(path.c_str());
  if (data.empty()) {
    syslog("{} don't exists, use default para!", path);
    return;
  }
  rapidjson::Document document;
  if (document.Parse(data.c_str()).HasParseError()) {
    syslog("{} parse fail, use default para!", path);
    return;
  }

  if (document.HasMember("apps_tailing_configs")) {
    const rapidjson::Value& childValue = document["apps_tailing_configs"];
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
void main() { ReadPackagePara(json_path); }