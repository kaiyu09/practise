
// Copyright (c) 2022, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// filepath.cpp : [file description]
//

#include <assert.h>

#include <filesystem>
#include <iostream>
#include <list>
#include <map>
#include <string>

#include "getopt.h"

namespace fs = std::filesystem;

static const fs::path demo_file_path =
    "/mnt/kai/kkrepo/code_c++/file/../file/filesystem/demotest";
static const fs::path bbbbb = "/mnt/yu/mywork/2868/parameters";

int main() {
  std::error_code err;

  if (fs::is_directory(demo_file_path, err)) {
    std::cout << demo_file_path << "is dir, " << err << std::endl;
  } else {
    std::cout << demo_file_path << "is not dir, " << err << std::endl;
  }

  if (fs::is_empty(demo_file_path, err)) {
    std::cout << demo_file_path << "is empty, " << err << std::endl;
  } else {
    std::cout << demo_file_path << "is not empty, " << err << std::endl;
  }
  if (!err) {
    std::cout << demo_file_path.filename().string() << "--filename-"
              << err.value() << std::endl;

    std::cout << demo_file_path.filename() << "--filename-" << err.value()
              << std::endl;
    std::cout << err.value() << std::endl;

    std::cout << demo_file_path.root_name() << "--root_name-" << err
              << std::endl;
    std::cout << demo_file_path.root_directory() << "--root_directory-" << err
              << std::endl;
    std::cout << demo_file_path.root_path() << "--root_path-" << err
              << std::endl;
    std::cout << demo_file_path.relative_path() << "--relative_path-" << err
              << std::endl;
    std::cout << demo_file_path.parent_path() << "--parent_path-" << err
              << std::endl;
    std::cout << demo_file_path.stem() << "--stem-" << err << std::endl;
    std::cout << demo_file_path.extension() << "--extension-" << err
              << std::endl;
  }

  return 0;
}
