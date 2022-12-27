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
# get_systemd_init.py : [file description]
#


import datetime
import subprocess


password = 'w+G)X8e)M5gwJ.*}wx,X'
cycle_times = 5
success_times = 0

def run_cmd(cmd):
    """ Run shell command.
    """
    process = subprocess.Popen([cmd], shell=True,
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    ret = process.returncode

    return [ret, stdout, stderr]


run_cmd("sudo mkdir -p {}".format(file_dir))

cmd_original = "imu-flash-util -f /mnt/flash/bundle/imu.hex -t 040"

cmd = "sudo sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.21 '{}'".format(
    password, cmd_original)

for i in range(cycle_times):

    run_cmd(cmd)
    if 
