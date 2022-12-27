#!/bin/bash

# Copyright (c) 2022, NIO Inc. All rights reserved.
#
# Any use, reproduction, distribution, and/or transfer of this file is strictly
# prohibited without the express written permission of the current copyright
# owner.
#
# Any licensed derivative work must retain this notice.
#
# test.sh : [file description]
#


dir='/home/nio/'

for file in $dir*; do
    echo $file
    echo ${file##*/}
done


