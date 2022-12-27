#include <climits>
#include <iostream>

int main(int argc, const char** argv) {
  char aa = 65;
  u_short b = -1;
  u_int a = -1;
  u_long c = -1;
  unsigned long long d = -1;

  std::cout << aa << std::endl
            << a << std::endl
            << b << std::endl
            << c << std::endl
            << d;

  long long ll_min = LLONG_MIN;
  long long ll_max = LLONG_MAX;
  unsigned long long ull_max = ULLONG_MAX;
  int int_max = INT_MAX;
  std::cout << std::endl
            << ll_min << " ; " << ll_max << " ; " << ull_max << " ; "
            << int_max;

  auto aaa = 1234;
  auto bbb = 1234L;

  std::cout << std::endl
            << sizeof(aaa) << " ; " << sizeof(bbb) << " ; " << std::endl;

  char ccc = 65;
  auto ddd = 'V';
  auto eee = "VVVVVVVVVV";
  std::cout << ccc << " ; " << 'B' << std::endl
            << sizeof(ddd) << " ; " << sizeof(eee) << std::endl;

  std::cout.put('S');

  return 0;  //编译器默认会加上, 没有这句编译不会报错.
}