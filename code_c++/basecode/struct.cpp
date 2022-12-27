
#include <iostream>
#include <map>
#include <vector>

typedef struct {
  std::string yu;
  int kai;
} kkk;

std::map<std::string, kkk> student = {
    {"aa", {"a", 31}},
    {"bb", {"b", 32}},
};

int NlogCmdResult(const std::string& res_str) {
  std::string split_str = "\n";
  std::string::size_type position;
  std::vector<std::string> result;

  int size = res_str.size();
  for (int i = 0; i < size; i++) {
    position = res_str.find(split_str, i);
    if (static_cast<int>(position) < size) {
      std::string fragment = res_str.substr(i, position - i);
      std::cout << fragment << std::endl;

      // NLOG_INFO("{}", fragment);
      i = position + split_str.size() - 1;
    }
  }
  return 0;
}

int main() {
  std::string abc =
      "qqqqqqqqqqq eeeeee   \n 222222222 22222211 1111\nkkkkkkk\n";
  NlogCmdResult(abc);

  const char* aaa = "china";
  std::string bbb = static_cast<std::string>(aaa);
  std::cout << aaa << std::endl;
  std::cout << bbb << std::endl;

  // for (auto &iter : student) {
  //   // std::cout << iter.first << std::endl;
  //   // std::cout << iter.second.yu << std::endl;
  //   // std::cout << iter.second.kai << std::endl;
  // }
}
