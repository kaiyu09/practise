
#include <iostream>
#include <map>
#include <vector>

typedef struct {
  std::string yu;
  int kai;
} kkk;

std::vector<kkk> kk_vec;

int main() {



  
  kk_vec.push_back({"aaa", 31});
  kk_vec.push_back({"bbb", 32});
  kk_vec.push_back({"ccc", 33});

  for (auto &iter : kk_vec) {
    std::cout << iter.yu << std::endl;
    std::cout << iter.kai << std::endl;
  }
}
