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

#include <atomic>
#include <functional>
#include <thread>





void FunctionModel(std::function<void()> func) { func(); };

int main() {
  template <class Function, class... Args>
  int StartTasks(Function && function, Args && ... args)




  {
FunctionModel, std::bind(std::forward<Function>(function), std::forward<Args>(args)...));
  }
}