#include <iostream>
// 必须的头文件
#include <pthread.h>

#include <mutex>
#include <string>
#include <thread>

using namespace std;

#define NUM_THREADS 5

// 线程的运行函数
void* say_hello(void* args) {
  // cout << "Hello Runoob！" << endl;
  printf("hello world!\n");
  return 0;
}

void testpthread() {
  // 定义线程的 id 变量，多个变量使用数组
  pthread_t tids[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; ++i) {
    //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
    int ret = pthread_create(&tids[i], NULL, say_hello, NULL);
    if (ret != 0) {
      cout << "pthread_create error: error_code=" << ret << endl;
    }
  }
  //等各个线程退出后，进程才结束；
  pthread_exit(NULL);
}

int main() {

  while (true) {
    printf("here0002\n");
    testpthread();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    printf("here0001\n");
  }
}