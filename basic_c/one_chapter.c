#include <stdio.h>
#define PRICE 56

int main(int argc, char const *argv[])
{
  printf("hello world!!\n");
  printf("PRICE\n");

  int aaa = PRICE;
  printf("aaa equal %d\n",aaa);


  float a,b,c;
  a=3.141592654;
  b=3.14e8;
  c=3.14;
  printf("a equal %f, b equal %f, c equal %f\n",a, b,c);


  char x,y;
  x='A';
  y='a';
  printf("x equal %6d or %c, y equal %6d or %c \n",x, x,y,y);
  printf("x equal %-6d or %c, y equal %-6d or %c \n",x, x,y,y);
  ;
  ;






  /* code */
  return 0;
}


// 程序 = 数据 + 算法