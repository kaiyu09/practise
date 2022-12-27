
#include <bitset>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

const char* source_path = "/nio/kk/test1.txt";
const char* target_path = "/nio/yy/test2.txt";
const char* multi_target_path[] = {"/nio/ll/test3.txt", "/nio/ll/test4.txt",
                                   "/nio/pp/test5.txt", "/nio/pp/test6.txt"};
static int InitParameter() {}

int main(int argc, char const* argv[]) {
  if (fs::exists(source_path)) {
    std::cout << source_path << " exist" << std::endl;
  }
  std::cout << source_path << " not exist" << std::endl;

  fs::path source_dir = ((fs::path)source_path).parent_path();
  if (!fs::exists(source_dir)) {
    fs
  }

  std::cout << "source dir is" << source_dir << std::endl;
  /* code */
  return 0;
}
