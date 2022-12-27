
#include <stdio.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

typedef struct {
  std::string yu;
  int kai;
} kkk;

std::vector<kkk> kk_vec;

int main() {
  printf("this is c++ pls repeat it:\n");
  // scanf 怎么使用呢
  auto kk_str = scanf;
  printf("%ld\n", kk_str);

  int number = std::cin.get();

  kk_vec.push_back({"aaa", number});
  kk_vec.push_back({"ccc", 33});
  kk_vec.push_back({"ccc", 33});
  kk_vec.push_back({"bbb", 32});
  kk_vec.push_back({"ccc", 33});

  std::cin.get();

  for (auto& iter : kk_vec) {
    std::cout << iter.yu << " : " << iter.kai << std::endl;
  }
  return 0;
}
