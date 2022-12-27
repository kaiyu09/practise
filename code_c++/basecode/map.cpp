
#include <iostream>
#include <map>
#include <string>

std::map<std::string, int> student = {
    {"aa", 31},
    {"bb", 32},
    {"cc", 33},
};
int main() {
  std::cout << "map" << std::endl;

  std::string kk = "fndkfnseb ";
  student.insert(make_pair(kk, 32));

  for (auto &iter : student) {
    std::cout << iter.first << " : ";
    std::cout << iter.second << std::endl;
    // std::cout << student.key << std::endl;
  }

  // std::cout << student["aa"] << std::endl;
  // std::string abc = "helloword\n";
  // printf("%s\n", abc.c_str());
  // printf("%ld\n", abc.size());
  // std::string sss("hello\0word\n", 20);
  // printf("%s\n", sss.c_str());
  // printf("%ld\n", sss.size());

  // std::string kktest = "yukai";
  // std::cout << kktest[0] << std::endl;
  // std::cout << kktest[1] << std::endl;
  // std::cout << kktest[2] << std::endl;
  // printf("%x\n", kktest[0]);
  // printf("%x\n", 16);

  // unsigned char cccc[] = {0x6d, 0x33, 0x47, 0x03, 0x00, 0x00,
  //                         0x00, 0x01, 0x00, 0x80, 0xfe};
  // for (int len = 0; len < 10; len++) {
  //   cccc[len] = 0x32;
  // }
  // for (int len = 0; len < 10; len++) {
  //   printf("%x\n", cccc[len]);
  //   printf("%d\n", cccc[len]);
  //   printf("%c\n", cccc[len]);
  // }
}
