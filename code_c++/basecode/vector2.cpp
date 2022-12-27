// Copyright (c) 2022, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// vector.cpp : [file description]
//
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

std::vector<int> kk_vec{1, 2};

int main() {
  kk_vec.push_back(7);
  kk_vec.push_back(8);
  kk_vec.emplace_back(9);
  kk_vec.emplace(kk_vec.begin(), 0);

  for (auto& iter : kk_vec) {
    std::cout << iter << std::endl;
  }

  std::vector<int>::iterator iteror;
  for (iteror = kk_vec.begin(); iteror != kk_vec.end(); iteror++) {
    std::cout << *iteror << std::endl;
  }

  for (int count = 0; count < kk_vec.size(); count++) {
    std::cout << kk_vec[count] << " position: " << count << std::endl;
  }

  std::map<std::string, int> kk_map = {{"yy", 12}, {"kk", 33}};
  for (int count = 0; count < kk_map.size(); count++) {
    std::cout << " position: " << count << std::endl;
  }

  // std::map<std::string, int>::iterator iter2;
  // for (iter2 = kk_map.begin(); iter2 != kk_map.end(); iter2++) {
  //   std::cout << iter2.first << std::endl;
  // }

  return 0;
}
