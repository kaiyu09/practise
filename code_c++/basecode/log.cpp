#include <cstdio>
#include <iostream>
#include <thread>

#include "getopt.h"
#include "syslog.h"

int main() {
  int64_t kknum = 0;
  int64_t total = 60 * 1024 * 1024 * 1024U;
  int64_t used = 59;
  int priority = 0;
  int priority2 = 0;
  if (used >= 0.8 * total) {
    priority = 10 - (total - used) / (0.02 * total);
    priority2 = 50 * used / total - 40;
  }
  std::cout << "\n::::\n" << priority << std::endl;
  std::cout << "\n::::\n" << priority2 << std::endl;

  while (false) {
    kknum++;
    syslog(LOG_WARNING, "Upload retry_times%ld", kknum);
    std::cout << "\nThat's all!\n" << kknum << std::endl;
    printf("1111111111111111111111111111111%ld", kknum);
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::microseconds(100));
  }
}