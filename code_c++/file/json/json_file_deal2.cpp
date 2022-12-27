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
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <boost/type_index.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

enum class SocNumber {
  kSoc1 = 1,
  kSoc2 = 2,
  kSoc3 = 3,
  kSoc4 = 4,
};

std::map<SocNumber, std::string> kSocMapping = {
    {SocNumber::kSoc1, "soc1"},
    {SocNumber::kSoc2, "soc2"},
    {SocNumber::kSoc3, "soc3"},
    {SocNumber::kSoc4, "soc4"},
};

static std::map<std::string, std::string> s1_net_mapping = {};
static std::map<std::string, std::string> s2_net_mapping = {};
static std::map<std::string, std::string> s3_net_mapping = {};
static std::map<std::string, std::string> s4_net_mapping = {};

static std::map<SocNumber, std::map<std::string, std::string>> all_net_mapping =
    {
        {SocNumber::kSoc1, s1_net_mapping},
        {SocNumber::kSoc2, s2_net_mapping},
        {SocNumber::kSoc3, s3_net_mapping},
        {SocNumber::kSoc4, s4_net_mapping},
};
// const std::string config_file_path =
//     "/home/nio/mazu/external/drive_os_sdk/nio_drive_os_patch/"
//     "nio_targetfs_patch/etc/ip_summary/ip_summary_mazu.json";
const std::string config_file_path =
    "/home/nio/kkrepo/code_c++/file/json/ip_summary_mazu.json";

std::string FileGetContents(const char* config_file_path) {
  if (config_file_path == nullptr) {
    printf("config_file_path:%s", config_file_path);
    return "";
  }
  std::ifstream in(config_file_path, std::ios::binary | std::ios::in);
  if (!in.is_open()) {
    printf("file open failed: %s\n", config_file_path);
    printf("error: %s\n", strerror(errno));
    return "";
  }
  std::ostringstream tmp;
  tmp << in.rdbuf();
  printf("tmp type: %s\n", boost::typeindex::type_id_with_cvr<decltype(tmp)>()
                               .pretty_name()
                               .c_str());
  return tmp.str();
}

int ReadPackagePara(const std::string& config_file_path) {
  printf("rurnurnrurn\n");
  std::string data = FileGetContents(config_file_path.c_str());
  printf("error2: %s\n", strerror(errno));

  if (data.empty()) {
    printf("error3: %s\n", strerror(errno));
    return -1;
  }
  rapidjson::Document document;
  if (document.Parse(data.c_str()).HasParseError()) {
    printf("error4: %s\n", strerror(errno));
    return -1;
  }

  for (auto& iter : kSocMapping) {
    std::string soc_name = iter.second.c_str();
    SocNumber soc_number = iter.first;

    if (document.HasMember(iter.second.c_str()) == false) {
      printf("error5: %s\n", strerror(errno));
      return -1;
    }

    printf("%s\n", iter.second.c_str());

    const rapidjson::Value& ip_array = document[iter.second.c_str()];

    for (auto it = ip_array.MemberBegin(); it != ip_array.MemberEnd(); ++it) {
      if (it->name.IsString() == false) {
        printf("error6: %s\n", strerror(errno));
        return -1;
      }
      if (it->value.IsString() == false) {
        printf("error7: %s\n", strerror(errno));
        return -1;
      }

      all_net_mapping[soc_number].insert(
          std::make_pair(it->name.GetString(), it->value.GetString()));
      printf("error8: %s\n", strerror(errno));
    }
  }

  for (auto& iter : all_net_mapping) {
    printf("%d \n", (int)iter.first);
    for (auto& it : iter.second) {
      printf("name  : %s  , \t", it.first.c_str());
      printf("string : %s\n", it.second.c_str());
    }
  }

  // for (rapidjson::SizeType i = 0; i < ip_array.Size(); ++i) {
  //   if (ip_array[i].IsObject() == false) {
  //     continue;
  //   }
  //   std::string net_name = ip_array[i].GetString();
  //   printf("%s\n", net_name.c_str());
  // }

  return 0;
}

int main() {
  printf("kkstart\n");
  ReadPackagePara(config_file_path);
  return 0;
}