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
# net_test.py : [file description]
#
import time
import subprocess


mima = 'w+G)X8e)M5gwJ.*}wx,X'
reset_cmd_str = "mcu_cmd -m 1 2 -c tegrareset x2 && mcu_cmd -m 1 2 -c tegrareset x1"

init_cmd_str_list = [
                "ssh-keygen -f '/home/nio/.ssh/known_hosts' -R '10.42.0.21'",
               "ssh-copy-id -o stricthostkeychecking=no -f mazu1",
               "w+G)X8e)M5gwJ.*}wx,X",
               "ssh-keygen -f '/home/nio/.ssh/known_hosts' -R '10.42.0.22'",
                "ssh-copy-id -o stricthostkeychecking=no -f mazu2",
               "w+G)X8e)M5gwJ.*}wx,X",
               "ssh-keygen -f '/home/nio/.ssh/known_hosts' -R '10.42.0.23'",
                "ssh-copy-id -o stricthostkeychecking=no -f mazu3",
               "w+G)X8e)M5gwJ.*}wx,X",
               "ssh-keygen -f '/home/nio/.ssh/known_hosts' -R '10.42.0.24'",
                "ssh-copy-id -o stricthostkeychecking=no -f mazu4",
               "w+G)X8e)M5gwJ.*}wx,X",
]



def run_cmd(cmd):
    """ Run shell command.
    """
    process = subprocess.Popen([cmd], shell=True,
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    ret = process.returncode

    return [ret, stdout, stderr]

for str in init_cmd_str_list:
    print(str)
