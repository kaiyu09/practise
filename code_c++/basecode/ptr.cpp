#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

std::string kk_string{};
std::vector<std::string> kk_vector{};
std::vector<int> kk_vector2{};

int main(int argc, const char** argv) {
  auto pointer = std::make_shared<int>(10);
  auto pointer2 = pointer;
  auto pointer3 = pointer;
  int* p = pointer.get();
  std::cout << typeid(pointer).name() << std::endl;
  std::cout << typeid(pointer2).name() << std::endl;
  std::cout << typeid(pointer3).name() << std::endl;
  std::cout << typeid(p).name() << std::endl;
  std::cout << typeid(kk_string).name() << std::endl;
  std::cout << typeid(kk_vector).name() << std::endl;
  std::cout << typeid(kk_vector2).name() << std::endl;

  std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;
  std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl;
  std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl;

  pointer2.reset();
  std::cout << "reset pointer2:" << std::endl;
  std::cout << "pointer.use_count() = " << pointer.use_count()
            << std::endl;  // 2
  std::cout << "pointer2.use_count() = " << pointer2.use_count()
            << std::endl;  // 0, pointer2 已 reset
  std::cout << "pointer3.use_count() = " << pointer3.use_count()
            << std::endl;  // 2
  pointer3.reset();
  std::cout << "reset pointer3:" << std::endl;
  std::cout << "pointer.use_count() = " << pointer.use_count()
            << std::endl;  // 1
  std::cout << "pointer2.use_count() = " << pointer2.use_count()
            << std::endl;  // 0
  std::cout << "pointer3.use_count() = " << pointer3.use_count()
            << std::endl;  // 0, pointer3 已 reset
  return 0;
}