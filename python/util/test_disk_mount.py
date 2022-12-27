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
import subprocess

disklist = [
    "/root_ro",
    "/root_rw",
    "/",
    "/tmp",
    "/var/log",
    "/dev",
    "/dev/shm",
    "/run",
    "/run/lock",
    "/sys/fs/cgroup",
    "/mnt/data",
    "/mnt/model",
    "/mnt/user_private",
    "/nio",
    "/mnt/flash",
    "/mnt/ramdisk",
    # "/nfs/s3/nio",
    # "/nfs/s1/nio",
    # "/nfs/s2/nio",
    # "/nfs/s4/nio",
    "/run/user/0",
]

password = 'w+G)X8e)M5gwJ.*}wx,X'
soclist = ["1", "2", "3", "4"]
time_str = str(datetime.datetime.now()).replace(" ", "--")
file_dir = "/home/nio/{}/".format(time_str)
print(file_dir)


def run_cmd(cmd):
    """ Run shell command.
    """
    process = subprocess.Popen([cmd], shell=True,
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    ret = process.returncode

    return [ret, stdout, stderr]


for soc_num in soclist:
    for disk in disklist:

        cmd_soc = "ls {}".format(
            disk)
        cmd_host = "sudo sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2{} '{}'".format(
            password, soc_num, cmd_soc)
        # print(cmd_host)+
        res = run_cmd(cmd_host)
        if res[0] != 0:
            print("ls error :soc{} , {}".format(soc_num, disk))

        cmd_soc = "dd if=/dev/urandom of={}/testdisk.file bs=1M count=10".format(
            disk)
        cmd_host = "sudo sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2{} '{}'".format(
            password, soc_num, cmd_soc)
        # print(cmd_host)
        res = run_cmd(cmd_host)
        if res[0] != 0:
            print("dd error :soc{} , {}".format(soc_num, disk))
