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
# filescp.py : [file description]
#


import subprocess


target_mazu_list = ["1", "2", "3", "4"]

basicdir = "/home/nio/mazu/external/drive_os_sdk/nio_drive_os_patch/nio_targetfs_patch"
file_path_list = [
    "/etc/rc.local",
    "/usr/bin/nio_vlan.sh",
    "/usr/lib/systemd/system/nio_vlan.service",
    "/usr/lib/systemd/system/vnstat.service"
]


def run_cmd(cmd):
    process = subprocess.Popen([cmd], shell=True,
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    ret = process.returncode

    return ret


mima = 'w+G)X8e)M5gwJ.*}wx,X'


choose = 2


if choose == 1:
    for mazu in target_mazu_list:
        rm_file_str = f"sshpass -p '{mima}' ssh -p 100{mazu} -o StrictHostKeyChecking=no -t root@10.110.193.62 rm -rf /root_rw/upper/*"

        rc = run_cmd(rm_file_str)
        if rc != 0:
            print("rm file: mazu{} failed".format(mazu))
        else:
            print("rm file: mazu{} success".format(mazu))

# kk mazu
if choose == 3:
    for mazu in target_mazu_list:

        rm_file_str = f"sshpass -p '{mima}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2{mazu} 'rm -rf /root_rw/upper/*'"
        print(rm_file_str)

        rc = run_cmd(rm_file_str)
        if rc != 0:
            print("rm file: mazu{} failed".format(mazu))
        else:
            print("rm file: mazu{} success".format(mazu))

if choose == 2:
    for file in file_path_list:
        source_file = basicdir + file
        for mazu in target_mazu_list:

            cmd_str = "sshpass -p '{}' scp -P100{} {} root@10.110.193.62:{}".format(mima,
                                                                                    mazu, source_file, file)
            # print(cmd_str)
            rc = run_cmd(cmd_str)
            print(rc)
            if rc != 0:
                print("scp file: {} failed".format(file))
            else:
                print("scp file:{} to mazu{} success".format(file, mazu))

    for mazu in target_mazu_list:
        link_str = f"sshpass -p '{mima}' ssh -p 100{mazu} -o StrictHostKeyChecking=no -t root@10.110.193.62 ln -s /lib/systemd/system/nio_vlan.service /etc/systemd/system/multi-user.target.wants/nio_vlan.service"

        rc = run_cmd(link_str)
        if rc != 0:
            print("ln file: mazu{} failed".format(mazu))
        else:
            print("ln file: mazu{} success".format(mazu))
# kk mazu
if choose == 4:
    for file in file_path_list:
        source_file = basicdir + file
        for mazu in target_mazu_list:

            cmd_str = "sshpass -p '{}' scp {} root@10.42.0.2{}:{}".format(
                mima, source_file, mazu, file)
            # print(cmd_str)
            rc = run_cmd(cmd_str)
            print(rc)
            if rc != 0:
                print("scp file: {} failed".format(file))
            else:
                print("scp file:{} to mazu{} success".format(file, mazu))

    for mazu in target_mazu_list:
        link_str = f"sshpass -p '{mima}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2{mazu} 'ln -s /lib/systemd/system/nio_vlan.service /etc/systemd/system/multi-user.target.wants/nio_vlan.service'"

        rc = run_cmd(link_str)
        if rc != 0:
            print("ln file: mazu{} failed".format(mazu))
        else:
            print("ln file: mazu{} success".format(mazu))
