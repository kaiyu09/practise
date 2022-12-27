#include <algorithm>
#include <cstdint>
#include <cstring>
#include <experimental/filesystem>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

std::string bin_data = "/home/nio/q.route.gz";
unsigned char m_eEPROMDataBuf[1024] = {};
unsigned char charstr;

// int main() {
//   std::ifstream binFile(bin_data, std::ios::binary);
//   if (binFile.is_open()) {
//     binFile.read((char*)&m_eEPROMDataBuf[0], 256);

//     std::cout << m_eEPROMDataBuf << std::endl;
//     printf("%s\n", m_eEPROMDataBuf);
//     printf("%ld\n", sizeof(m_eEPROMDataBuf));
//     printf("%ld\n", sizeof(m_eEPROMDataBuf));
//   }
//   binFile.close();
// }
int main() {
  std::ifstream binFile(bin_data, std::ios::binary);
  if (binFile.is_open()) {
    std::string data2 = std::string(std::istreambuf_iterator<char>(binFile),
                                    std::istreambuf_iterator<char>());

    printf("%s\n", data2.c_str());
    printf("%ld\n", sizeof(data2));
    printf("%ld\n", data2.size());
  }
  binFile.close();
}