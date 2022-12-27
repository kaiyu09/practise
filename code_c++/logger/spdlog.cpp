// Copyright (c) 2022, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// spdlog.cpp : [file description]
//

#include "spdlog/spdlog.h"

#include <stdlib.h>

int main(int argc, const char** argv) {
  spdlog::info("info log");
  auto ret = system("ls -lh ~/");

  spdlog::info("{}", ret);
  return 0;
}
