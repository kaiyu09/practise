
#include <iostream>

int main(int argc, char const *argv[]) {
  int a = 2;
  int d = 2;
  int b = 0;
  int c = 0;

  b = (a++ + 4) + (a++ + 6);
  c = (4 + d++) + (6 + d++);
  std::cout << a << " , " << b << " , " << c << std::endl;
  /* code */
  return 0;
}
