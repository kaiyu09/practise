
#include <iostream>
#include <map>
#include <string>

int hexStrToInt(std::string hexStr) { return stoi(hexStr, 0, 16); }

std::string intToHexStr(int mask) {
  int hexLen = 0;

  for (int i = 2; i <= 6; i += 2) {
    std::string hex = "";
    for (int j = 0; j < i; j++) {
      hex += "F";
    }
    if (mask <= hexStrToInt(hex)) {
      hexLen = i;
      break;
    }
  }

  if (hexLen == 0) {
    hexLen = 8;
  }

  std::string hexes[16] = {"0", "1", "2", "3", "4", "5", "6", "7",
                           "8", "9", "A", "B", "C", "D", "E", "F"};
  std::string hexstring = "";
  for (int i = 0; i < hexLen; i++) {
    int j = hexLen - i - 1;
    int number = (mask >> 4 * j) & 0xf;
    hexstring += hexes[number];
  }
  return hexstring;
}

int main() {
  int a = 2634031120;
  printf("a=%d\n", a);
  printf("a=%x\n", a);
  printf("a=%s\n", intToHexStr(a).c_str());
}
