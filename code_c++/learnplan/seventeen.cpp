// Copyright (c) 2022, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// eight.cpp : [file description]
//

// read a file contents and write it into another file
#include <climits>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, const char** argv) {
  std::string input_str;
  std::cin >> input_str;
  if (input_str == "std") {
    std::cout << "std:: dwuehdw" << std::endl;

  } else if (input_str == "err") {
    std::cerr << "err:: gsefvds" << std::endl;
  } else if (input_str == "log") {
    std::clog << "log:: xkashdk" << std::endl;
  }

  std::cout.put('a').put('b').put(43);

  std::string kk = "ilovechina";
  std::cout.write(kk.c_str(), 32);

  return 0;  // 编译器默认会加上, 没有这句编译不会报错.
}