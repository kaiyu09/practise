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

# No space for directory leaf checksum. Please run e2fsck -D

import time
import datetime
import subprocess
import random


time_str = str(datetime.datetime.now()).replace(" ", "--")
log_file_name = "{}_ext4_test_nio.log".format(time_str)

passwd = 'w+G)X8e)M5gwJ.*}wx,X'
passwd_mazu = '_7NVg3Tta3*Rd!40g@gZ'
reset_cmd_str = "mcu_cmd -m 1 2 -c aurixreset"
shutdown_cmd = "echo 1 > /sys/class/tegra_hv_pm_ctl/tegra_hv_pm_ctl/device/trigger_sys_shutdown"

shunt_dowm_list = [
    "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.21 '{}'".format(
        passwd, shutdown_cmd),
    "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.22 '{}'".format(
        passwd, shutdown_cmd),
    "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.23 '{}'".format(
        passwd, shutdown_cmd),
    "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.24 '{}'".format(
        passwd, shutdown_cmd),
]

cmd_sub = '"No space for directory leaf checksum"'
cmd_sub = '"Structure needs cleaning"'
cmd_sub = '"EXT4-fs error"'

cmd_lists = [
    "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.21 'dmesg | grep {}'".format(
        passwd, cmd_sub),
    "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.22 'dmesg | grep {}'".format(
        passwd, cmd_sub),
    "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.23 'dmesg | grep {}'".format(
        passwd, cmd_sub),
    "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.24 'dmesg | grep {}'".format(
        passwd, cmd_sub),
]


cmd_mazu_lists = [
    "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t mazu@10.42.0.21 'dmesg | grep {}'".format(
        passwd_mazu, cmd_sub),
    "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t mazu@10.42.0.22 'dmesg | grep {}'".format(
        passwd_mazu, cmd_sub),
    "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t mazu@10.42.0.23 'dmesg | grep {}'".format(
        passwd_mazu, cmd_sub),
    "sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t mazu@10.42.0.24 'dmesg | grep {}'".format(
        passwd_mazu, cmd_sub),
]


def run_cmd(cmd):
    process = subprocess.Popen([cmd], shell=True,
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    ret = process.returncode
    stdout, stderr = process.communicate()
    return [ret, stdout, stderr]


cycle_times = 0
test_times = 0
error_times = 0

while True:
    cycle_times = cycle_times + 1
    print("cycle_times: ", str(cycle_times))
    print(str(datetime.datetime.now()))
    time_ramdon = random.randint(2, 10)
    print("random wait time:", time_ramdon)
    time.sleep(time_ramdon)

    # 重启mazu
    run_cmd(reset_cmd_str)
    # for cmd in shunt_dowm_list:
    #     rc = run_cmd(cmd)
    time.sleep(300)

    log_cmd = "date >> ~/{}".format(log_file_name)
    run_cmd(log_cmd)

    # 检查log中的关键字
    print("&"*200)
    for cmd in cmd_mazu_lists:
        rc = run_cmd(cmd)
        test_times += 1
        print(rc[0])
        print(rc[1])
        print(rc[2])

        if rc[1] != b'':
            report_str = "{}, case catched".format(cmd)
            print(rc[1])
            error_times += 1
        else:
            report_str = "{}, no case".format(cmd)

        print(report_str)

        log_cmd = "echo {} >> ~/{}".format(report_str, log_file_name)
        run_cmd(log_cmd)

        con_str = "total test times= {}, failure times= {}".format(
            test_times, error_times)
        print(con_str)

        log_cmd = "echo {} >> ~/{}".format(con_str, log_file_name)
        run_cmd(log_cmd)
