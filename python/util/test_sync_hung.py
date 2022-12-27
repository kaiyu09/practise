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
# test_sync_hung.py : [file description]
#


import os
import time
import argparse
import subprocess


password = "w+G)X8e)M5gwJ.*}wx,X"


def run_cmd(cmd):
    process = subprocess.Popen([cmd], shell=True,
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    ret = process.returncode
    return [ret, stdout.decode('utf-8', 'replace').strip(), stderr.decode('utf-8', 'replace').strip()]


def parse_args():
    parser = argparse.ArgumentParser(description="sync task test")
    parser.add_argument("-t",
                        "--hung_timeout",
                        type=int,
                        default=120,
                        help="hung_task_timeout_secs")
    parser.add_argument("-s",
                        "--soc_num",
                        type=int,
                        default=1,
                        help="target soc_num")
    parser.add_argument("-d",
                        "--dirty_ratio",
                        type=int,
                        default=5,
                        help="dirty_ratio")
    parser.add_argument("-b",
                        "--dirty_bg_ratio",
                        type=int,
                        default=2,
                        help="dirty_bg_ratio")
    parser.add_argument("-c",
                        "--cycle_times",
                        type=int,
                        default=10,
                        help="cycle_times")
    parser.add_argument("-m",
                        "--mountpoint",
                        type=str,
                        default="/mnt/flash",
                        help="mountpoint")
    parser.add_argument("-p",
                        "--disk",
                        type=str,
                        default="/dev/vblkdev6",
                        help="/dev/vblkdev6")

    args = parser.parse_args()
    return args


class SyncTest(object):
    def __init__(self, args):

        self.dirty_ratio = args.dirty_ratio
        self.dirty_bg_ratio = args.dirty_bg_ratio

        self.disk = args.disk
        self.soc_num = args.soc_num
        self.mountpoint = args.mountpoint
        self.hung_timeout = args.hung_timeout
        self.cycle_times = args.cycle_times

        self.file_name = "test_file_7g"
        self.local_file_path = "/tmp/{}".format(self.file_name)

        self.is_hung_occurs = False

        self.mcu = (self.soc_num + 1)//2
        self.index = 2-(self.soc_num % 2)

        self.cmd_dict = {"enable_fast_commit": "tune2fs -O fast_commit {}".format(self.disk),
                         "disable_fast_commit": "tune2fs -O ^fast_commit {}".format(self.disk),

                         "set_dirty_ratio": "echo {} > /proc/sys/vm/dirty_ratio".format(self.dirty_ratio),
                         "reset_dirty_ratio": "echo 20 > /proc/sys/vm/dirty_ratio",
                         "set_dirty_bg_ratio": "echo {} > /proc/sys/vm/dirty_background_ratio".format(self.dirty_bg_ratio),
                         "reset_dirty_bg_ratio": "echo 10 > /proc/sys/vm/dirty_background_ratio",

                         "set_hung_timeout": "echo {} > /proc/sys/kernel/hung_task_timeout_secs".format(self.hung_timeout),
                         "disable_hung_panic": "echo 0 > /proc/sys/kernel/hung_task_panic",

                         "do_sync": "sync",
                         "empty_disk": "rm -rvf {}/*".format(self.mountpoint),
                         "creat_file1_7g": "dd if=/dev/urandom of={} bs=1M count=7000".format(self.local_file_path),
                         "copy_file_to_soc": "scp {} root@10.42.0.2{}:{}/".format(self.local_file_path, self.soc_num, self.mountpoint),
                         "delete_file1_7g": "rm -rvf {}/{}".format(self.mountpoint, self.file_name),


                         "count_hung_times": "dmesg | grep -c wb_wait_for_completion",
                         "check_hung_event": "dmesg | grep wb_wait_for_completion",

                         "reboot_soc": "mcu_cmd -m {} -c tegrareset x{}".format(self.mcu, self.index),

                         }

    def run_remote_cmd(self, cmd):
        remote_cmd = "sudo sshpass -p '{}' ssh -o StrictHostKeyChecking=no root@10.42.0.2{} '{}'".format(
            password, self.soc_num, cmd)

        process = subprocess.Popen([remote_cmd], shell=True,
                                   stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        ret = process.returncode
        return [ret, stdout.decode('utf-8', 'replace').strip(), stderr.decode('utf-8', 'replace').strip()]

    def basic_init(self):
        self.run_remote_cmd(self.cmd_dict["empty_disk"])
        self.run_remote_cmd(self.cmd_dict["set_hung_timeout"])
        self.run_remote_cmd(self.cmd_dict["disable_hung_panic"])

        self.run_remote_cmd(self.cmd_dict["disable_fast_commit"])
        self.run_remote_cmd(self.cmd_dict["reset_dirty_ratio"])
        self.run_remote_cmd(self.cmd_dict["reset_dirty_bg_ratio"])

    def set_dirty_ratio(self):
        self.run_remote_cmd(self.cmd_dict["disable_fast_commit"])
        self.run_remote_cmd(self.cmd_dict["set_dirty_ratio"])
        self.run_remote_cmd(
            self.cmd_dict["set_dirty_bg_ratio"])

    def copy_file_to_disk(self):
        if os.path.isfile(self.local_file_path):
            size = round(os.path.getsize(self.local_file_path) /
                         1024.0/1024.0/1024.0, 2)
            print("file {} exist, size= {}G".format(self.local_file_path, size))

        else:
            print("{} is not file, creating new one".format(self.local_file_path))
            run_cmd("sudo rm -rf {}".format(self.local_file_path))
            run_cmd(self.cmd_dict["creat_file1_7g"])
            print("file {} created".format(self.local_file_path))

        print("file {} copying to soc{}".format(
            self.local_file_path, self.soc_num))
        ret = run_cmd(self.cmd_dict["copy_file_to_soc"])
        print("file copy done, ret={},{},{}".format(ret[0], ret[1], ret[2]))

    def sync_and_count_hung(self):
        self.run_remote_cmd(self.cmd_dict["do_sync"])
        ret = self.run_remote_cmd(self.cmd_dict["count_hung_times"])
        print("count hung times= {}".format(ret[1]))
        if ret[1] != "0":
            self.is_hung_occurs = True
        ret = self.run_remote_cmd(self.cmd_dict["check_hung_event"])
        print(ret[1])

    def reboot_soc_and_wait(self):

        ret = run_cmd(self.cmd_dict["reboot_soc"])
        print(ret[1])
        print("sleeping 30 seconds for soc waking up")
        time.sleep(30)

    def task_start(self):
        self.total_hung_times = 0
        for i in range(self.cycle_times):
            times = i+1
            print(
                "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- cycle times {} testing...".format(times))
            self.basic_init()
            self.copy_file_to_disk()
            self.sync_and_count_hung()
            if self.is_hung_occurs:
                self.total_hung_times += 1
            print("cycle times {} test done, hung= {}, total hung= {}".format(
                times, self.is_hung_occurs, self.total_hung_times))
            self.reboot_soc_and_wait()

        print("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- total test time= {}, hung times= {}".format(
            self.cycle_times, self.total_hung_times))


if __name__ == '__main__':
    args = parse_args()
    sync = SyncTest(args)
    sync.task_start()
