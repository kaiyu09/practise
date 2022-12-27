
#include <cstring>
#include <filesystem>
#include <iostream>

int main(int argc, char const* argv[]) {
  std::filesystem::path kkpath = "/home/nio/kkrepo/code_c++/basecode/fs";
  std::filesystem::path yypath = "./test.txt";

  std::cout << kkpath.root_path() << std::endl;
  std::cout << yypath.root_path() << std::endl;

  const char* path[] = {"/mnt/yu/mywork/2124", "/mnt/yu/mywork/5837",
                        "/mnt/yu/mywork/certs.tar.gz"};

  for (int i = 0; i < 3; i++) {
    std::cout << path[i] << std::endl;
  }

  const char* abc = "";
  int a = atoi(abc);
  std::cout << a << std::endl;

  const char* bbb = "b";
  int len = strlen(bbb);
  std::cout << len << std::endl;

  /* code */
  return 0;
}
