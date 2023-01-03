#include <stdio.h>
#include <unistd.h>
#define PRICE 56

void PrintDemo() { printf("hello world!!\n"); }

int main(int argc, char const *argv[]) {
  PrintDemo();
  fork();
  PrintDemo();
  fork();
  PrintDemo();
  sleep(3);


  return 0;
}

// 程序 = 数据 + 算法