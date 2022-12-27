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

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "/home/nio/kkrepo/code_c++/rapidjson-v1.1.0/include/rapidjson/document.h"
#include "/home/nio/kkrepo/code_c++/rapidjson-v1.1.0/include/rapidjson/prettywriter.h"
#include "/home/nio/kkrepo/code_c++/rapidjson-v1.1.0/include/rapidjson/stringbuffer.h"
#include "/home/nio/kkrepo/code_c++/rapidjson-v1.1.0/include/rapidjson/writer.h"

static const std::string json_path =
    "/home/nio/kkrepo/code_c++/file/log_manager.json";
void ReadPackagePara(const std::string& path);

void ReadPackagePara(const std::string& path) {
  printf("rurnurnrurn\n");

  std::ifstream content(path, std::ios::binary | std::ios::in);
  std::ostringstream tmp;
  tmp << content.rdbuf();
  auto data = tmp.str();

  if (data.empty()) {
    printf("file don't exists!\n");
    return;
  }
  rapidjson::Document document;
  if (document.Parse(data.c_str()).HasParseError()) {
    printf("file parse fail, use default para!\n");
    return;
  }

  if (document.HasMember("apps_tailing_configs")) {
    printf("apps_tailing_configs found!\n");

    const rapidjson::Value& childValue = document["apps_tailing_configs"];
    auto config_array = childValue.GetArray();
    printf("%d\n", childValue.Size());
    printf("%d\n", childValue.IsArray() );
    printf("%d\n", childValue[0].IsObject() );
    printf("%d\n", childValue[0].HasMember("app_name") );
    printf("%d\n", childValue[0].HasMember("app_name") );
    printf("%s\n", childValue[0]["app_name"].GetString() );
    printf("%d\n", childValue[0]["is_s2_need_log"].GetBool() );





    // for (rapidjson::SizeType i = 0; i < childValue.Size(); ++i) {
    //     printf("%d\n", childValue[i].Size());
    // }
  }

  // std::cout << "int& childValue: type is " << typeid(childValue).name()
  //           << std::endl;
  // std::cout << "int& config_array: type is " << typeid(config_array).name()
  //           << std::endl;
  //   rapidjson::Value::ConstMemberIterator iter =
  //       document.FindMember("split_size");

  //   if (iter != document.MemberEnd()) {
  //     split_max_size_ = iter->value.GetInt() * kUnitMB;
  //   }

  //   iter = document.FindMember("package_max_size");
  //   if (iter != document.MemberEnd()) {
  //     package_max_size_ = iter->value.GetInt() * kUnitMB;
  //   }
}
int main() { ReadPackagePara(json_path); }