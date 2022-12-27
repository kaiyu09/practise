#include <math.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// int  readBinFile(std::string& filename, void*& bufPtr, int& pointNum, int
// pointDim)

int main() {
  std::streampos fileSize;  //实例化fpos用于表示窄向流中的位置。
  std::ifstream file("/home/nio/test_file.gz", std::ios::binary);
  if (!file.is_open()) {
    cout << "open file failed !!" << endl;
    return 0;
  }
  // get its size:

  //把文件的读指针结尾位置向后移0个字节
  file.seekg(0, std::ios::end);
  fileSize = file.tellg();
  cout << "fileSize: " << fileSize << endl;

  //把文件的写指针从文件开头向后移 0 个字节
  file.seekg(0, std::ios::beg);

  int length = fileSize;
  double* f2 = new double[length];

  std::ifstream ifs("/home/nio/test_file.gz", std::ios::binary | std::ios::in);
  ifs.read((char*)f2, sizeof(double) * length);
  ifs.close();

  cout << f2 << endl;
  for (int i = 0; i < length; i++) {
    // std::cout << i << ": " << f2[i] << std::endl;
    printf("%d : %x", i, f2[i]);
  }
  return 0;
}
// read the data: