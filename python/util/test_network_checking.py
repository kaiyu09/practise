#!/usr/bin/env python3
# -*- coding:utf-8 -*-

# Copyright (c) 2022, NIO Inc. All rights reserved.
#
# Any use, reproduction, distribution, and/or transfer of this file is strictly
# prohibited without the express written permission of the current copyright
# owner.
#
# Any licensed derivative work must retain this notice.
#
# test_network_checking.py : [file description]
#


import time
import datetime
import subprocess


time_str = str(datetime.datetime.now()).replace(" ", "--")
log_file_name = "{}_net_test_nio.log".format(time_str)

passwd = 'w+G)X8e)M5gwJ.*}wx,X'
reset_cmd_str = "mcu_cmd -m 1 2 -c tegrareset x2 && mcu_cmd -m 1 2 -c tegrareset x1"

ping_s1_str = ["ping -c 4 10.42.0.21",
               "ping -c 4 10.42.0.22",
               "ping -c 4 10.42.0.23",
               "ping -c 4 10.42.0.24",

               "ping -c 4 172.20.1.21",
               "ping -c 4 172.20.1.29",
               "ping -c 4 172.20.2.21",
               "ping -c 4 172.20.3.21",
               "ping -c 4 172.20.4.21",
               "ping -c 4 172.20.5.21",

               "ping -c 4 172.20.1.22",
               "ping -c 4 172.20.2.22",
               "ping -c 4 172.20.3.22",
               "ping -c 4 172.20.4.22",
               "ping -c 4 172.20.5.22",

               "ping -c 4 172.20.1.23",
               "ping -c 4 172.20.2.23",
               "ping -c 4 172.20.3.23",
               "ping -c 4 172.20.4.23",
               "ping -c 4 172.20.5.23",

               "ping -c 4 172.20.1.24",
               "ping -c 4 172.20.2.24",
               "ping -c 4 172.20.3.24",
               "ping -c 4 172.20.4.24",
               "ping -c 4 172.20.5.24",

               "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.21 'ping -c 4 baidu.com'".format(
                   passwd),
               "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.21 'ping -c 4 v-stg.nioint.com'".format(
                   passwd),
               "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.22 'ping -c 4 baidu.com'".format(
                   passwd),
               "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.22 'ping -c 4 v-stg.nioint.com'".format(
                   passwd),
               "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.23 'ping -c 4 baidu.com'".format(
                   passwd),
               "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.23 'ping -c 4 v-stg.nioint.com'".format(
                   passwd),
               "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.24 'ping -c 4 baidu.com'".format(
                   passwd),
               "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.24 'ping -c 4 v-stg.nioint.com'".format(
                   passwd),
               ]


def run_cmd(cmd):
    """ Run shell command.
    """
    process = subprocess.Popen([cmd], shell=True,
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    ret = process.returncode

    return [ret, stdout, stderr]


cycle_times = 0
error_times = 0
while True:
    cycle_times = cycle_times + 1
    print("times: ", str(cycle_times))
    print(str(datetime.datetime.now()))
    time.sleep(2)
    # 重启mazu
    run_cmd(reset_cmd_str)
    time.sleep(30)
    log_cmd = "date >> ~/{}".format(log_file_name)
    run_cmd(log_cmd)

    for cmd in ping_s1_str:
        rc = run_cmd(cmd)
        if rc[0] == 0:
            report_str = "{} success".format(cmd)
        else:
            report_str = "{} failed".format(cmd)
            error_times = error_times + 1
            print("&"*100)
            # input()
        print(report_str)
        log_cmd = "echo {} >> ~/net_test_nio.log".format(report_str)
        run_cmd(log_cmd)

        con_str = "total test times{}, ping failure times= {}".format(
            cycle_times, error_times)
        print(con_str)
        log_cmd = "echo {} >> ~/net_test_nio.log".format(con_str)
        run_cmd(log_cmd)
