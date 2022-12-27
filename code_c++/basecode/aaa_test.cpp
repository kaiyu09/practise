
// Copyright (c) 2022, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// aaa_test.cpp : [file description]
//

#include <iostream>
#include <map>

#include "getopt.h"

enum class FaultStatus {
  kDefault = 0,
  kNotExist = 1,
  kExist = 2,
  kMax = 3,
};

FaultStatus number_max = FaultStatus::kMax;

int main() {
  std::map<FaultStatus, std::string> todo_state = {
      {FaultStatus::kDefault, "kDefault"},
      {FaultStatus::kNotExist, "kNotExist"},
  };

  for (auto &iter_a : todo_state) {
    std::cout << "FaultStatus" << (int)iter_a.first << iter_a.second << std::endl;
  }

  for (int iter = 0; iter < (int)number_max; iter = iter + 1) {
    std::cout << "FaultStatus" << iter << std::endl;
    std::cout << "FaultStatus" << iter << std::endl;
  }
}

