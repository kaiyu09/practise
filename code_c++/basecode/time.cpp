
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
#include <assert.h>

#include <iostream>
#include <list>
#include <string>

static constexpr int kDateStrMax = 20;

std::string traffic_eth_ports_name[] = {
    "eth1.30",
    "eth1.40",
};
int main() {
  time_t t = time(0);
  char ch[8];
  strftime(ch, sizeof(ch), "%Y-%m", localtime(&t));
  std::string month_string_spec = "";
  month_string_spec = (std::string)ch + "-01";
  std::cout << month_string_spec << std::endl;

  int64_t num = 1223234354646465;
  int64_t testnum;
  testnum = num / 1024 / 1024;
  std::cout << testnum << std::endl;

  // // list 的基本用法:::赞赞赞!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // std::list<std::string> slist = {"eth1", "eth2", "eth3", "eth4"};
  // std::list<std::string>::iterator iter = slist.begin();
  // for (iter; iter != slist.end(); iter++) {
  //   std::cout << *iter << std::endl;
  // }
  // // list 的基本用法:::赞赞赞!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // for (auto &iiter : slist) {
  //   std::cout << iiter << std::endl;
  // }

  std::string arraystring[] = {"a", "b", "c"};
  for (auto &s : arraystring) {
    std::cout << s << std::endl;
  }

  return 0;
}
