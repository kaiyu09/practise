// Copyright (c) 2022, NIO Inc. All rights reserved.
//
// Any use, reproduction, distribution, and/or transfer of this file is strictly
// prohibited without the express written permission of the current copyright
// owner.
//
// Any licensed derivative work must retain this notice.
//
// sa_net_state.cpp : [file description]
//
#include "sa_net_state.h"

#include <iostream>

#include "syslog.h"

namespace tsp_client {

int num = 1;
static bool IsMazuEnvProd() {
  // char* tmp_env = (char*)"prod";
  // auto res = SetCertEnv(tmp_env);
  // if (res == 0) {
  //   syslog(LOG_INFO, "set env=prod success");
  // } else {
  //   syslog(LOG_INFO, "set env=prod failed");
  // }

  static CertInfo* cert_info = GetPrivCertInfo();
  if (cert_info->env == kCertEnvProd) {
    return true;
  } else {
    return false;
  }
}

bool SaNetState::IsNetAccessible() {
  if (!IsMazuEnvProd()) {
    syslog(LOG_INFO, "sa_net_status: mazu env is not prod, no sa net checking");
    return true;
  }

  CellularNetworkState net_status = GetCellularNetworkState();

  // srand(time(NULL));
  // int nums = rand() % 3;
  // if (nums == 0) {
  //   net_status.is_connected = true;
  //   syslog(LOG_WARNING, "sa_net_status: random set true connected, %d",
  //          net_status.is_connected);

  // } else {
  //   net_status.is_connected = false;
  //   syslog(LOG_WARNING, "sa_net_status: random set false connected, %d",
  //          net_status.is_connected);
  // }

  if (!net_status.is_connected) {
    is_state_satisfied = false;
    if (is_state_changed) {
      syslog(LOG_WARNING, "sa_net_status: net is not connected");
    }
  } else if (net_status.channel_status == NO_CONNECTION) {
    is_state_satisfied = false;
    if (is_state_changed) {
      syslog(LOG_WARNING, "sa_net_status: no wifi or cellular net connected");
    }
  } else if (net_status.signal_strength_level == INVALID ||
             net_status.signal_strength_level == NO_SIGNAL_OR_UNKNOWN) {
    is_state_satisfied = false;
    if (is_state_changed) {
      syslog(LOG_WARNING,
             "sa_net_status: signal_strength_level is not satisfied");
    }
  } else {
    is_state_satisfied = true;
    if (is_state_changed) {
      syslog(LOG_INFO, "sa_net_status: net recovered");
    }
  }




  if (is_state_satisfied_pre != is_state_satisfied) {
    is_state_satisfied_pre = is_state_satisfied;
    is_state_changed = true;
  } else {
    is_state_changed = false;
    syslog(LOG_WARNING,
           "sa_net_status: sa net state not chang, pre: %d , now %d",
           is_state_satisfied_pre, is_state_satisfied);
  }

  if (is_state_satisfied == true) {
    if (is_state_changed) {
      syslog(LOG_INFO, "sa_net_status: signal_strength_level is %d",
             net_status.signal_strength_level);
    }
    return true;
  } else {
    if (is_state_changed) {
      syslog(LOG_INFO, "sa_net_status: mazu env is prod, sa net not ready");
    }
    return false;
  }
}

}  // namespace tsp_client
