#include <stdio.h>

#include <unistd.h>
#define PRICE 56

int main(int argc, char const *argv[])
{
  printf("hello world!!\n");
  fork();
  printf("hello world 22!!\n");

  fork();
  printf("hello world 33!!\n");

  sleep(20);

  return 0;
}


// 程序 = 数据 + 算法