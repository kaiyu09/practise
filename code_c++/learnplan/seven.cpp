
#include <iostream>

int recurive(int);
int reduce(int);
int reduce_typea(int *);

int main(int argc, char const *argv[]) {
  recurive(5);

  int a = 3;
  std::cout << a << std::endl;
  std::cout << reduce(a) << std::endl;
  std::cout << a << std::endl;

  int b = 3;
  std::cout << b << std::endl;
  int *p;
  p = &b;
  std::cout << reduce_typea(p) << std::endl;
  std::cout << b << std::endl;

  return 0;
}

int recurive(int count) {
  std::cout << "this cycle count equal= " << count << std::endl;
  if (count > 0) {
    count--;
  } else {
    return 0;
  }

  recurive(count);

  std::cout << "that cycle count equal= " << count + 1 << std::endl;
  return 0;
}

int reduce(int number) {
  number = number - 2;
  return number;
}
int reduce_typea(int *number) {
  *number = *number - 2;
  return *number;
}
