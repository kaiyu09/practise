// Copyright (c) 2022, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// string.cpp : [file description]
//

#include <iostream>
#include <string>
// using string constructors

int main() {
  using namespace std;

  string one("china winner");
  cout << one << endl;

  string two(one);
  cout << two << endl;

  string three(one, 3, string::npos);
  cout << three << endl;

  string five(20, 73);
  cout << five << endl;

  const char* kk = "ilovechinaandshanghai";
  string ll(kk, 10);
  cout << ll << endl;
  string yy(kk, 10, string::npos);
  cout << yy << endl;

  std::string zero_string{""};
  std::string test = zero_string.substr(0, string::npos);
  cout << test << string::npos << endl;
}
