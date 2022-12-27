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
# test_fsync_wtith_fast_commit.py : [file description]
#

import os
import time
import zipfile
import fnmatch
import shutil
import tarfile


flash_dir_fileaa = "/mnt/flash/fileaa"
flash_dir_filecc = "/mnt/flash/filecc"
flash_dir_filebb = "/mnt/flash/filebb"
flash_dir_filedd = "/mnt/flash/filedd"
flash_dir_fileee = "/mnt/flash/fileee"


def test_fsync_time():

    os.system("rm -rf /mnt/flash/*")

    os.system(
        "dd if=/dev/urandom of={} bs=1M count=200 >/dev/null 2>&1".format(flash_dir_fileaa))
    os.system(
        "dd if=/dev/urandom of={} bs=1M count=200 >/dev/null 2>&1".format(flash_dir_filecc))
    os.system(
        "dd if=/dev/urandom of={} bs=1M count=200 >/dev/null 2>&1".format(flash_dir_filebb))
    os.system(
        "dd if=/dev/urandom of={} bs=1M count=200 >/dev/null 2>&1".format(flash_dir_filedd))
    os.system(
        "dd if=/dev/urandom of={} bs=1M count=200 >/dev/null 2>&1".format(flash_dir_fileee))

    os.system("sync&")
    start = time.time()
    os.system("nfsync {}".format(flash_dir_filecc))
    end = time.time()
    time.sleep(2)
    return (end-start)


cycle_times = 200

os.system("tune2fs -O fast_commit /dev/vblkdev6")
print("enable___"*10)
timelist = []
for i in range(cycle_times):
    ret = test_fsync_time()
    timelist.append(ret)
print("/"*100)
print(timelist, "average:", sum(timelist)/len(timelist))
print("/"*100)

print("disable___"*10)


os.system("tune2fs -O ^fast_commit /dev/vblkdev6")
timelist = []
for i in range(cycle_times):
    ret = test_fsync_time()
    timelist.append(ret)
print("/"*100)
print(timelist, "average:", sum(timelist)/len(timelist))
print("/"*100)
