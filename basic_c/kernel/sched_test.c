#include <bits/types/struct_sched_param.h>
#include <errno.h>
#include <linux/sched.h>
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PRICE 56

int main(int argc, char const *argv[]) {
  printf("hello world!!\n");
  fork();
  printf("hello world 22!!\n");

  fork();
  printf("hello world 33!!\n");

  sleep(1);

  __pid_t pid = getppid();
  printf("current thread pid is %d\n", pid);

  int sched_type = sched_getscheduler(pid);
  printf("current thread pid sched_type is %d\n", sched_type);

  sleep(1);
  struct sched_param param_init;
  int res = sched_getparam(pid, &param_init);
  printf("current thread sched_getparam res is %d, param_init is %d \n", res,
         param_init.sched_priority);

  sleep(1);
  // try to change sched_param
  struct sched_param param_changed = {20};
  int param = sched_setscheduler(pid, 2, &param_changed);
  printf("current thread sched_setscheduler res is %d, param_changed is %d \n",
         param, param_changed.sched_priority);
  printf("%s/n", strerror(errno));
  sleep(1);

  return 0;
}

// 程序 = 数据 + 算法
