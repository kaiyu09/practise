// Copyright (c) 2022, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// knowledge.cpp : [file description]
//
#include <array>
#include <filesystem>
#include <iostream>
#include <map>

// A.B    则A为对象或者结构体；
// A->B
// 则A为指针，->是成员提取，A->B是提取A中的成员B，A只能是指向类、结构、联合的指针；
// A::B   是作用域运算符，A::B表示作用域A中的名称B，A可以是名字空间、类、结构；
// A：B   一般用来表示继承；

// C++——char* vs std::string vs char[]
// array 容器的用法

// array<int,3> ,第一个参数表示数组中元素的类型，第二个表示数组的大小。

int main() {
  std::string output = "bsjdfbsjfb";
  auto res = output.find("bsj");

  std::array<std::string, 3> kkarray={"a","b","c"};

  std::cout << kkarray[0] <<  kkarray[1] << kkarray[2] <<std::endl;

  std::cout << std::get<0>(kkarray) <<  kkarray.at(1) << kkarray[2] <<std::endl; // 3  methods for std::array

  // std::filesystem::exists("/nio/logs");
}
