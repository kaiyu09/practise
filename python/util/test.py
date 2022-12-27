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


a = [1, 2, 3, 4]


for soc in a:
    mcu = (soc+1)//2
    index = 2-(soc % 2)
    print(soc, mcu, index)


abc = "yuki,hdsjf.\n"
print(abc)
print(abc.strip("\n"))
print(abc.strip("\n"))
print(abc.strip("\n"))


aaa = "yu"
bbb = "kk"

ccc = "{:<10}: {:<}, \n".format(aaa, bbb)
print(ccc)
