#include <bits/types/struct_sched_param.h>
#include <errno.h>
#include <linux/sched.h>
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// 在标准C/C++中，最小的计时单位是一毫秒.

int main(int argc, char const *argv[]) {
  int sleep_time = 1;
  clock_t start_time;
  clock_t finish_time;
  printf("hello world!!\n");
  fork();
  printf("hello world 22!!\n");

  fork();
  printf("hello world 33!!\n");
  sleep(sleep_time);

  start_time = clock();

  __pid_t pid = getppid();
  printf("current thread pid is %d\n", pid);
  sleep(sleep_time);

  int sched_type = sched_getscheduler(pid);
  printf("current thread pid sched_type is %d\n", sched_type);

  sleep(sleep_time);
  struct sched_param param_init;
  int res = sched_getparam(pid, &param_init);
  printf("current thread sched_getparam res is %d, param_init is %d \n", res,
         param_init.sched_priority);

  sleep(sleep_time);
  // try to change sched_param
  struct sched_param param_changed = {20};
  int policy = 2;
  int param = sched_setscheduler(pid, policy, &param_changed);
  printf("sched_setscheduler res= %d, param_changed= %d, policy= %d\n", param,
         param_changed.sched_priority, policy);
  sleep(sleep_time);

  sched_type = sched_getscheduler(pid);
  printf("current thread pid sched_type is %d\n", sched_type);
  sleep(sleep_time);

  printf("%s\n", strerror(errno));

  sleep(sleep_time);
  finish_time = clock();
  float program_time = (float)(finish_time - start_time);
  printf("program cost time is %f\n", program_time);
  return 0;
}

// 程序 = 数据 + 算法
