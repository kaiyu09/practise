// Copyright (c) 2022, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// thread_mgr.h : [file description]
//

#include <stdio.h>

#include <iostream>
#include <list>
#include <string>

int main(int argc, char const *argv[]) {
  // std::string cmd = "ls -lh";

  // auto ret = std::system(cmd.c_str());
  // std::cout << ret << std::endl;

  // popen

  std::list<std::string> stdout_list;
  char outBuffer[1024];
  const char *cmdStr = "ls -lh";

  FILE *pipeLine = popen(cmdStr, "r");
  if (!pipeLine) {
    perror("Fail to popen\n");
    return 1;
  }
  // perror("Fail to popen\n");
  std::cout << pipeLine << std::endl;

  while (fgets(outBuffer, 1024, pipeLine) !=
         NULL) {  // 获取输出从文件中读取字符串，每次只读取一行
    stdout_list.emplace_back(outBuffer);
  }
  pclose(pipeLine);

  for (auto &iter : stdout_list) {
    std::cout << iter;
  }

  /* code */
  return 0;
}
