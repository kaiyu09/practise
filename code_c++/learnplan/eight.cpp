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

int function(int i, const char* kk) {
  std::cout << "this is type one: int= " << i << " char*= "
            << "kk" << std::endl;
  return 0;
}

int function(const char* kk, int i) {
  std::cout << "this is type two: int= " << i << " char*= "
            << "kk" << std::endl;
  return 0;
}

int main(int argc, const char** argv) {
  std::ifstream file;
  std::filesystem::path file_path =
      "/home/nio/kkrepo/code_c++/learnplan/kktest.file";
  file.open(file_path.c_str());
  if (file.is_open()) {
    std::cout << file_path.c_str() << "open success" << std::endl;
  }

  std::ofstream aa_file;
  std::filesystem::path aa_file_path =
      "/home/nio/kkrepo/code_c++/learnplan/aa_kktest.file";
  aa_file.open(aa_file_path.c_str());
  if (aa_file.is_open()) {
    std::cout << aa_file_path.c_str() << "open success" << std::endl;
    aa_file << (std::string)("china") << " people" << std::endl;
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string abc(buffer.str());
  std::cout << "abc: " << abc << std::endl;
  aa_file << abc << std::endl;

  file.close();
  aa_file.close();

  function(100, "china");
  function("china", 100);

  const char* a = "1234";
  std::cout << a << std::endl;
  a = "4444";
  std::cout << a << std::endl;
  std::string b = "1234";

  return 0;  //编译器默认会加上, 没有这句编译不会报错.
}