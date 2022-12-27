#include <iostream>

int aaaa = 32;

static constexpr const char* kYou = "love china";

int main() {
  std::cout << "yukai" << std::endl;
  decltype(aaaa) bbbb;
  decltype(bbbb) cccc;
  printf("%s\n", typeid(bbbb).name());
  printf("%s\n", typeid(cccc).name());

  const char* kk = "";
  kk = kYou;
  std::cout << kk << std::endl;
  std::cout << typeid(kk).name() << std::endl;
}