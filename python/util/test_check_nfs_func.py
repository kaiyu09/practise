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
log_file_name = "{}_nfs_test_nio.log".format(time_str)

passwd = 'w+G)X8e)M5gwJ.*}wx,X'
genstr = 'ssh -o StrictHostKeyChecking=no -t root@10.42.0.21'
reset_soc_cmd_str = "mcu_cmd -m 1 2 -c tegrareset x2 && mcu_cmd -m 1 2 -c tegrareset x1"
reset_cmd_str = "mcu_cmd -m 1 2 -c aurixreset"

ping_s1_str = [
    "sshpass -p '{}' {} 'ls /nfs/s1/nio/'".format(passwd, genstr),
    "sshpass -p '{}' {} 'ls /nfs/s2/nio/'".format(passwd, genstr),
    "sshpass -p '{}' {} 'ls /nfs/s3/nio/'".format(passwd, genstr),
    "sshpass -p '{}' {} 'ls /nfs/s4/nio/'".format(passwd, genstr),
]


def run_cmd(cmd):
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
    # reboot mazu
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
            print(report_str)
            log_cmd = "echo {} >> ~/{}".format(report_str, log_file_name)
            run_cmd(log_cmd)
            input()

        print(report_str)
        log_cmd = "echo {} >> ~/{}".format(report_str, log_file_name)
        run_cmd(log_cmd)

        log_cmd2 = "echo stdout:{},std:err{} >> ~/{}".format(
            rc[1], rc[2], log_file_name)
        run_cmd(log_cmd2)

        con_str = "total test cycle times{}, cmd fail times= {}".format(
            cycle_times, error_times)
        print(con_str)
        log_cmd = "echo {} >> ~/{}".format(con_str, log_file_name)
        run_cmd(log_cmd)
