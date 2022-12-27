// Copyright (c) 2022, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// sa_net_state.h : [file description]
//
#pragma once

#include "cellular_network_state.h"
#include "cert_info.h"

namespace tsp_client {

class SaNetState {
 public:
  bool IsNetAccessible();

 private:
  bool is_state_changed = false;
  bool is_state_satisfied = true;
  bool is_state_satisfied_pre = true;
};

}  // namespace tsp_client
