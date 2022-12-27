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
# test_nfs_limit.py : [file description]
#


import time
import argparse
import threading
import subprocess

soc_list = [1, 2, 3, 4]


def run_cmd(cmd):
    process = subprocess.Popen([cmd], shell=True,
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    ret = process.returncode
    return [ret, stdout.decode('utf-8', 'replace').strip(), stderr.decode('utf-8', 'replace').strip()]


def parse_args():
    parser = argparse.ArgumentParser(description="did_cmd")
    parser.add_argument("-v",
                        "--verbose",
                        type=str,
                        default=False,
                        help="print out detail log")

    args = parser.parse_args()
    return args


def get_remote_cmd(soc_num, cmd):
    passwd = 'w+G)X8e)M5gwJ.*}wx,X'
    remote_cmd = "sudo sshpass -p '{}' ssh -o StrictHostKeyChecking=no root@10.42.0.2{} '{}'".format(
        passwd, soc_num, cmd)
    return remote_cmd


class AppStartTimeTest(object):
    def __init__(self, args):
        self.verbose = args.verbose
        # self.app_start_time = "grep -nr run_nio_apps.*Start /nio/logs/latest/syslog.log* | head -n 1 | egrep -o 'used [0-9]{1}.[0-9]{2}s'"
        self.app_start_time = "grep -nr run_nio_apps.*Start /nio/logs/latest/syslog.log*"
        self.reboot_mazu = "mcu_cmd -m 1 2 -c aurixreset x1"
        self.log_sync = "nfsync /nio/logs"

    def test(self):

        ret = run_cmd(self.reboot_mazu)
        print(ret[0], ret[1], ret[2])
        time.sleep(30)
        for soc_num in soc_list:
            cmd_str = get_remote_cmd(soc_num, self.app_start_time)
            ret = run_cmd(cmd_str)
            print(ret[0], ret[1], ret[2])

        time.sleep(10)
        for soc_num in soc_list:
            cmd_str = get_remote_cmd(soc_num, self.log_sync)
            ret = run_cmd(cmd_str)
            print(ret[0], ret[1], ret[2])


if __name__ == '__main__':
    args = parse_args()
    app = AppStartTimeTest(args)

    while(1):
        app.test()
