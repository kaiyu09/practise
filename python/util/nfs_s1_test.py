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
# test_disk_mount.py : [file description]
#


import datetime
import time
import subprocess


password = 'w+G)X8e)M5gwJ.*}wx,X'
time_str = str(datetime.datetime.now()).replace(" ", "--")
soc_num = "1"
file_dir = "/home/nio/{}/".format(time_str)

error_times = 0
# print(file_dir)


def run_cmd(cmd):
    """ Run shell command.
    """
    process = subprocess.Popen([cmd], shell=True,
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    ret = process.returncode

    return [ret, stdout, stderr]


for i in range(100):

    reset_soc = "mcu_cmd -m 1  -c tegrareset x1 x2"
    res = run_cmd(reset_soc)
    print(res)
    time.sleep(20)

    cmd_soc = "ls /nio/sshfs_1/ /nio/samba_1/ /nio/nfs_1/"
    cmd_host = "sudo sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2{} '{}'".format(
        password, soc_num, cmd_soc)
    # print(cmd_host)+
    res = run_cmd(cmd_host)
    if res[0] != 0:
        error_times += 1
    print(res[1])
    print("ls *******************************error {}".format(error_times))
