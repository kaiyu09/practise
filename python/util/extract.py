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


# my_tar = tarfile.open('my_tar.tar.gz')
# my_tar.extractall('./my_folder')  # specify which folder to extract to
# my_tar.close()


# my_tar = tarfile.open('my_tar.tar.gz')
# my_tar.extract('hello.txt', './my_folder')
# my_tar.close()


source_dir = "/mnt/yu/mywork/5435/bundle"
target_dir = "/mnt/yu/mywork/5435/pbfile"

add_file = "/mnt/yu/mywork/5435/kk.insert"


tarfilelist = []

for dirname, dirnames, filenames in os.walk(source_dir):
    for filename in filenames:
        if filename.endswith(".tar.gz"):
            tarfilelist.append(dirname+"/"+filename)
print(tarfilelist)

for file in tarfilelist:
    bundle = tarfile.open(file, "a:")
    print(bundle)

    list = bundle.getnames()
    # bundle.addfile(add_file)
    # bundle.add(add_file)
    bundle.addfile(add_file)
    # bundle.makedir("test")
    print(list)

for file in tarfilelist:
    bundle = tarfile.open(file, "r")
    print(bundle)

    list = bundle.getnames()
    print(list)

    for name in list:
        # print(name)
        if name.endswith(".pb"):
            print(name)
            bundle.extract(name, target_dir)
    bundle.close()
