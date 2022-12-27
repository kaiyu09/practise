// Copyright (c) 2022, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// resume50qa.c : [file description]
//
#include <cstdio>
#include <cstring>
#include <string>

int main(int argc, char const *argv[]) {
  const std::string basestr = "11111111";
  const char *cstring = "11111111";

  int a = sizeof(basestr);
  int b = strlen(cstring);
  printf("%d,%d,%d,%d\n", a, b, (int)basestr.length(), (int)basestr.size());
  printf("abc");
  return 0;
}
