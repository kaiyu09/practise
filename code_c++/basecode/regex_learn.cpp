// Copyright (c) 2022, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// regex_learn.cpp : [file description]
//

#include <iostream>
#include <iterator>
#include <regex>
#include <string>

int main() {
  const std::string s = "Quick brown fox.";

  std::regex words_regex("[^\\s]+");
  auto words_begin = std::sregex_iterator(s.begin(), s.end(), words_regex);
  auto words_end = std::sregex_iterator();

  std::cout << "Found " << std::distance(words_begin, words_end) << " words:\n";

  for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
    std::smatch match = *i;
    std::string match_str = match.str();
    std::cout << match_str << '\n';
  }
}

