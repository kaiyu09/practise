// Copyright (c) 2022, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// proto_convert.cpp : [file description]
//
#include <nio_flash.pb.h>
#include <stdio.h>
#include <stdlib.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

// enum FlashType {
//   kAll = 0,
//   kSilence = 1,
//   kNonSilence = 2,
// };

// enum BundleType {
//   kFull = 0,
//   kDiff = 1,
// };

// struct FlashFile {
//   std::string type;
//   std::string path;
//   std::string hash;
// };
// struct FlashPackage {
//   std::string name;
//   std::string flash_gate;
//   std::string switch_gate;
//   std::string software_version;
//   std::string hardware_version;
//   BundleType bundle_type;
//   FlashType flash_type;
//   bool is_skip;
//   bool is_allow_fail;
//   int file_list;
// };

// struct Configure {
//   std::string target_name;  // Used to print DEBUG information
//   std::string lib_name;     // load library files in local or bundle
//   FlashPackage FlashPackage;
// };

// Configure bundle_configure;
// Configure isp_configure;
// Configure gnss_configure;
// Configure svc_configure;
// Configure switch_configure;

// std::map<std::string, Configure> components_map{
//     {"imu", bundle_configure},       {"gnss", gnss_configure},
//     {"isp", isp_configure},       {"svc", svc_configure},
//     {"switch", switch_configure},
// };

int generate_pb(std::string &name, std::string &content) {
  std::string sub_dir = "/mazu_flash_pb/";
  std::string home_dir = std::getenv("HOME");
  home_dir = "./";
  std::string full_dir = home_dir + sub_dir;

  // namespace fs = std::filesystem;
  std::filesystem::create_directory(full_dir);

  std::string pb_out_path = full_dir + name + ".pb";
  printf("%s\n", pb_out_path.c_str());
  std::fstream output(pb_out_path, std::ios::out | std::ios::trunc);
  if (!output.is_open()) {
    printf("file open failed\n");
  }
  output.write(content.c_str(), content.length());
  output.close();
  return 0;
}

int mazu_config_init() {
  nio_flash::Configure bundle_config;
  std::string name = "mazu";
  bundle_config.set_target_name(name);
  bundle_config.set_lib_name("local");

  auto string = bundle_config.DebugString();
  // auto string = bundle_config.DebugString();
  generate_pb(name, string);
  return 0;
}

int imu_config_init() {
  nio_flash::Configure bundle_config;
  std::string name = "imu";
  bundle_config.set_target_name(name);
  bundle_config.set_lib_name("");

  auto flash_package = bundle_config.add_flash_package();
  flash_package->set_name("imu");
  flash_package->set_software_version("AG040_V3.14_150");
  auto string = bundle_config.DebugString();
  generate_pb(name, string);
  return 0;
}

int isp_config_init() {
  nio_flash::Configure bundle_config;
  std::string name = "isp";
  bundle_config.set_target_name(name);
  bundle_config.set_lib_name("");
  auto flash_package = bundle_config.add_flash_package();
  flash_package->set_name("isp");
  flash_package->set_software_version("20220310202203102026NIO_MAZU_DVR");
  auto string = bundle_config.DebugString();
  generate_pb(name, string);
  return 0;
}

int svc_config_init() {
  nio_flash::Configure bundle_config;
  std::string name = "svc";
  bundle_config.set_target_name(name);
  bundle_config.set_lib_name("");

  auto flash_package = bundle_config.add_flash_package();
  flash_package->set_name("svc_front");
  flash_package->set_software_version("8");

  auto flash_package_2 = bundle_config.add_flash_package();
  flash_package_2->set_name("svc_back");
  flash_package_2->set_software_version("8");

  auto flash_package_3 = bundle_config.add_flash_package();
  flash_package_3->set_name("svc_right");
  flash_package_3->set_software_version("8");

  auto flash_package_4 = bundle_config.add_flash_package();
  flash_package_4->set_name("svc_left");
  flash_package_4->set_software_version("8");
  auto string = bundle_config.DebugString();
  generate_pb(name, string);
  return 0;
}

int gnss_config_init() {
  nio_flash::Configure bundle_config;
  std::string name = "gnss";
  bundle_config.set_target_name(name);
  bundle_config.set_lib_name("");

  auto flash_package = bundle_config.add_flash_package();
  flash_package->set_name("gnss_m");
  flash_package->set_software_version("LG69TAINR01A04V01");

  auto flash_package_2 = bundle_config.add_flash_package();
  flash_package_2->set_name("gnss_s");
  flash_package_2->set_software_version("LG69TAJNR01A04V01");

  auto string = bundle_config.DebugString();
  generate_pb(name, string);
  return 0;
}

int switch_config_init() {
  nio_flash::Configure bundle_config;
  std::string name = "switch";
  bundle_config.set_target_name(name);
  bundle_config.set_lib_name("");

  auto flash_package = bundle_config.add_flash_package();
  flash_package->set_name("switch_1");
  flash_package->set_software_version("1.0.6");

  auto flash_package_2 = bundle_config.add_flash_package();
  flash_package_2->set_name("switch_2");
  flash_package_2->set_software_version("1.0.6");

  auto string = bundle_config.DebugString();
  generate_pb(name, string);
  return 0;
}

int main() {
  mazu_config_init();

  imu_config_init();
  isp_config_init();
  gnss_config_init();
  svc_config_init();
  switch_config_init();

  return 0;
}
