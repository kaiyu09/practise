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

soc_num=1
mcu_num=1

j=100
hung_times=0
for ((i = 1; i <= j; i++)); do
    echo "normal_mode test cycle times = ${i} "
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'echo 20 > /proc/sys/vm/dirty_ratio'
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'echo 10 > /proc/sys/vm/dirty_background_ratio'
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'tune2fs -O ^fast_commit /dev/vblkdev6'

    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'rm -rf /mnt/flash/*'
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'echo 60 > /proc/sys/kernel/hung_task_timeout_secs'
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'sync'
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' scp /mnt/yu/bundle/full_bundle/file7g root@10.42.0.2${soc_num}:/mnt/flash/
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'sync'
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'ls -lh /mnt/flash/'
    is_panic=$(sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no root@10.42.0.2${soc_num} 'dmesg | grep -c wb_wait_for_completion')
    if [ ${is_panic} != 0 ]; then
        hung_times=$((${hung_times} + 1))
    fi
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'dmesg | grep wb_wait_for_completion'
    mcu_cmd -m ${mcu_num} -c aurixreset
    echo "wait soc reboot"
    echo "aaaaaaaaaa total hung times = ${hung_times}"
    sleep 30
done
echo "eeeeeeeeeeeeeeeeee normal_mode total hung times = ${hung_times}"

j=100
hung_times=0
for ((i = 1; i <= j; i++)); do
    echo "dirty_mem set mode test cycle times = ${i} "
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'echo 5 > /proc/sys/vm/dirty_ratio'
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'echo 2 > /proc/sys/vm/dirty_background_ratio'
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'tune2fs -O ^fast_commit /dev/vblkdev6'

    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'rm -rf /mnt/flash/*'
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'echo 60 > /proc/sys/kernel/hung_task_timeout_secs'
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'sync'
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' scp /mnt/yu/bundle/full_bundle/file7g root@10.42.0.2${soc_num}:/mnt/flash/
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'sync'
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'ls -lh /mnt/flash/'
    is_panic=$(sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no root@10.42.0.2${soc_num} 'dmesg | grep -c wb_wait_for_completion')
    if [ ${is_panic} != 0 ]; then
        hung_times=$((${hung_times} + 1))
    fi
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'dmesg | grep wb_wait_for_completion'
    mcu_cmd -m ${mcu_num} -c aurixreset
    echo "wait soc reboot"
    echo "aaaaaaaaaa total hung times = ${hung_times}"
    sleep 30
done
echo "eeeeeeeeeeeeeeeeee dirty_mem total hung times = ${hung_times}"

j=100
hung_times=0
for ((i = 1; i <= j; i++)); do
    echo "fast_commit mode test cycle times = ${i} "
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'echo 20 > /proc/sys/vm/dirty_ratio'
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'echo 10 > /proc/sys/vm/dirty_background_ratio'
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'tune2fs -O fast_commit /dev/vblkdev6'

    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'rm -rf /mnt/flash/*'
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'echo 60 > /proc/sys/kernel/hung_task_timeout_secs'
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'sync'
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' scp /mnt/yu/bundle/full_bundle/file7g root@10.42.0.2${soc_num}:/mnt/flash/
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'sync'
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'ls -lh /mnt/flash/'
    is_panic=$(sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no root@10.42.0.2${soc_num} 'dmesg | grep -c wb_wait_for_completion')
    if [ ${is_panic} != 0 ]; then
        hung_times=$((${hung_times} + 1))
    fi
    sudo sshpass -p 'w+G)X8e)M5gwJ.*}wx,X' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2${soc_num} 'dmesg | grep wb_wait_for_completion'
    mcu_cmd -m ${mcu_num} -c aurixreset
    echo "wait soc reboot"
    echo "aaaaaaaaaa total hung times = ${hung_times}"
    sleep 30
done
echo "eeeeeeeeeeeeeeeeee fast_commit total hung times = ${hung_times}"
