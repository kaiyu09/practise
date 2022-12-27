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
# extract.py : [file description]
#


import os
import zipfile
import fnmatch
import shutil
import tarfile


source_dir = "/mnt/yu/mywork/6676/s1"
tarfilelist = []


def find_all_targz_file(source_dir):
    for dirname, dirnames, filenames in os.walk(source_dir):
        for filename in filenames:
            if filename.endswith(".tar.gz"):
                tarfilelist.append(
                    {"dir": dirname, "path": dirname+"/"+filename})
    # print(tarfilelist)


def do_decompress_task(tarfilelist):

    for file in tarfilelist:
        os.chdir(file["dir"])
        print(os.getcwd())
        bundle = tarfile.open(file["path"], "r")
        list = bundle.getnames()
        for name in list:
            if name.endswith(".log"):
                target_file = file["dir"]+name
                print(name, target_file)
                bundle.extract(name, target_file)
        bundle.close()


find_all_targz_file(source_dir)
do_decompress_task(tarfilelist)
