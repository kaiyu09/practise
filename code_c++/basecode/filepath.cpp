
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
#include <string>

#include "getopt.h"

namespace fs = std::filesystem;
static const fs::path aaaaa = "/mnt/flash/tmp";
static const fs::path bbbbb = "/mnt/flash/tmp/";

int main() {
  fs::path a = aaaaa;
  fs::path b = bbbbb;

  if (a == b) {
    std::cout << "equl" << std::endl;
  }
  std::cout << a.c_str()<< "\n" << b.c_str() << std::endl;

  std::string arraystring[] = {"a", "b", "c"};
  for (auto &s : arraystring) {
    std::cout << s << std::endl;
  }
  std::string abc = "kai";
  std::cout << abc << std::endl;
  abc.assign("kkk");
  std::cout << abc << std::endl;

  return 0;
}
