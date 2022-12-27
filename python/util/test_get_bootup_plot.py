e4#!/usr/bin/env python3
# -*- coding:utf-8 -*-

# Copyright (c) 2022, NIO Inc. All rights reserved.
#
# Any use, reproduction, distribution, and/or transfer of this file is strictly
# prohibited without the express written permission of the current copyright
# owner.
#
# Any licensed derivative work must retain this notice.
#
# get_systemd_plot.py : [file description]
#


import datetime
import subprocess
import os


file_name = "boot_startup.svg"
password = 'w+G)X8e)M5gwJ.*}wx,X'
soclist = ["1", "2", "3", "4"]
home_dir = os.path.expandvars('$HOME')

time_str = str(datetime.datetime.now()).replace(" ", "--")
file_dir = "{}/{}/".format(home_dir, time_str)
print(file_dir)


systemd_analyze_cmd_list = [
    "systemctl list-jobs",
    "systemctl stop log_manager.service\
        systemd-update-utmp-runlevel.service\
            preloadlibservice.service nv_security_setup_run_once.service\
                multi-user.target sys-devices-virtual-net-mgbe2_0.200.device\
                    nv_ist_client.service",
    "systemd-analyze",
    # "systemd-analyze blame",
    "systemd-analyze plot > {}".format(file_name),
]


def run_cmd(cmd):
    """ Run shell command.
    """
    process = subprocess.Popen([cmd], shell=True,
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    ret = process.returncode

    return [ret, stdout, stderr]


run_cmd("sudo mkdir -p {}".format(file_dir))

for soc_num in soclist:
    for cmd_original in systemd_analyze_cmd_list:
        cmd = "sudo sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2{} '{}'".format(
            password, soc_num, cmd_original)
        print(cmd)
        run_cmd(cmd)
        rc = run_cmd(cmd)
        if rc[0] == 0:
            print("{} success".format(cmd_original))
        else:
            print("{} failed".format(cmd_original))
    local_file_path = "{}s{}_boot_startup.svg".format(file_dir, soc_num)
    cmd_scp = "sudo sshpass -p '{}' scp root@10.42.0.2{}:~/{} {}".format(
        password, soc_num, file_name, local_file_path)
    print(cmd_scp)
    rc = run_cmd(cmd_scp)
    if rc[0] == 0:
        print("{} success".format(cmd_scp))
    else:
        print("{} failed".format(cmd_scp))
