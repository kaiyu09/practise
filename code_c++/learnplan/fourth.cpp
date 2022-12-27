#include <array>
#include <climits>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

struct info_T {
  int a;
  int b : 4;
};

enum kk {
  aa,
  bb,
  cc,
};

int main(int argc, const char** argv) {
  char charr[20];
  std::string string;
  std::cout << strlen(charr) << " ; " << strlen(string.c_str()) << std::endl;

  info_T info1;
  info1.a = 200;
  info1.b = 200;
  std::cout << info1.a << " ; " << info1.b << std::endl;

  kk test1;
  kk test2;
  test1 = aa;
  test2 = cc;
  std::cout << test1 << " ; " << test2 << std::endl;

  // pointer

  int* p_int_a = new int;
  *p_int_a = 32;
  std::cout << *p_int_a << " ; " << p_int_a << std::endl;
  delete p_int_a;
  std::cout << *p_int_a << " ; " << p_int_a << std::endl;

  int* p_array = new int[100]{0, 1, 2, 3, 4};
  std::cout << *p_array << " ; " << p_array[3] << " len: " << sizeof *p_array
            << std::endl;
  delete p_array;

  int p_array_var[100]{0, 1, 2, 3, 4};
  std::cout << p_array_var << " ; " << p_array_var[3]
            << " len: " << sizeof p_array_var / sizeof *p_array_var << " ; "
            << std::endl;

  char char_array[10] = "abcdef";
  std::cout << char_array << " ; " << char_array[4] << " ; " << char_array[9]
            << std::endl;

  int array[5]{2, 4, 6, 8, 0};
  std::array<int, 5> aint = {6, 7, 8, 9, 0};
  std::vector<int> vint(5);
  vint[0] = 1;
  vint[1] = 2;
  vint[2] = 3;
  vint[3] = 4;
  vint[4] = 5;

  for (auto& iter : array) {
    std::cout << iter << ",";
  }
  std::cout << std::endl;

  for (auto& iter : vint) {
    std::cout << iter << ",";
  }
  std::cout << std::endl;

  for (auto& iter : aint) {
    std::cout << iter << ",";
  }
  // std::cout << std::endl;

  return 0;  //编译器默认会加上, 没有这句编译不会报错.
}