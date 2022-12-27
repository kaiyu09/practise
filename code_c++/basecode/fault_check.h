// Copyright (c) 2022, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// fault_check.h : [file description]
//
#pragma once

#include <thread>
#include <vector>

#include <nsingleton.h>

namespace calibration {

class FaultCheck {
public:
  ~FaultCheck();
  void Start();
  void Stop();

private:
  void CheckCalibFileHandler();
  /* data */
  std::thread th_file_check_;
  bool need_publish_;
  bool is_terminate_;

  NDECLARE_SINGLETON(FaultCheck)
};

} // namespace calibration
