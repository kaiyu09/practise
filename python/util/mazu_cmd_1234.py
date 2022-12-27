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


file_name = "kk_startup.svg"
password = 'w+G)X8e)M5gwJ.*}wx,X'
soclist = ["1", "2", "3", "4"]
time_str = str(datetime.datetime.now()).replace(" ", "--")
file_dir = "/home/nio/{}/".format(time_str)
print(file_dir)


def init_mazu_ssh():
    for soc_num in soclist:
        cmd = "ssh-keygen -f '/root/.ssh/known_hosts' -R '10.42.0.2{}'".format(
            soc_num)
        print(cmd)
        rc = run_cmd(cmd)
        print(rc)

def run_mazu_cmd(cmd_original):
    for soc_num in soclist:
        cmd = "sudo sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2{} '{}'".format(
            password, soc_num, cmd_original)
        print(cmd)
        rc = run_cmd(cmd)
        print(rc)

def copy_file_to_mazu(local_file, mazu_file):
    for soc_num in soclist:
        cmd = "sudo sshpass -p '{}' scp -o StrictHostKeyChecking=no {} root@10.42.0.2{}:{}".format(
            password, local_file, soc_num, mazu_file)
        print(cmd)
        rc = run_cmd(cmd)
        print(rc)

def run_cmd(cmd):
    """ Run shell command."""
    process = subprocess.Popen([cmd], shell=True,
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    ret = process.returncode
    return [ret, stdout, stderr]


init_mazu_ssh()
run_mazu_cmd("systemctl stop log_manager")

local_file = "/home/nio/mazu/build/linux/debug/apps/log_manager/log-manager"
mazu_file = "/bin/log-manager"
copy_file_to_mazu(local_file, mazu_file)

local_file = "~/mazu/external/drive_os_sdk/nio_drive_os_patch/nio_targetfs_patch/etc/log_manager.json"
mazu_file = "/etc/log_manager.json"
copy_file_to_mazu(local_file, mazu_file)

run_mazu_cmd("systemctl restart log_manager")

run_mazu_cmd("ls /nio/logs/latest/")