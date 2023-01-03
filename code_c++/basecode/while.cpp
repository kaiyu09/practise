
#include <sys/stat.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

typedef struct {
  std::string yu;
  int kai;
} kkk;

std::vector<kkk> kk_vec;
std::string path = "boot12345";
std::string path = "/media/nio/kaiyu/practise/code_c++/basecode/aaa_test";

int main() {
  kk_vec.push_back({"aaa", 31});
  kk_vec.push_back({"bbb", 32});
  kk_vec.push_back({"ccc", 33});

  for (auto &iter : kk_vec) {
    std::cout << iter.yu << std::endl;
    std::cout << iter.kai << std::endl;
  }

  int test = std::atoi(path.substr(1, 10).c_str());
  printf("%d\n", test);

  mode_t mode{12};
  int chmod(path.c_str(), mode);
  return 0;
}
