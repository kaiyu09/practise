// Copyright (c) 2022, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// aa_test.cpp : [file description]
//

#include <iostream>

#include "bb_test.h"
#include "aa_test.h"

int ccPrintFuncName() {
  std::cout << "cc_test" << std::endl;
  return 0;
}

int main(int argc, const char** argv) {
  std::cout << "function name: cc_test" << std::endl;
  aaPrintFuncName();
  aaPrintFuncName();
  ccPrintFuncName();
  return 0;
}