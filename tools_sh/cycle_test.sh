#!/bin/bash
i=0
times=20
while [ $i -le $times ]; do
    let i+=1
    ${imu-flash-util -f /mnt/flash/bundle/imu.hex -t 040}
    echo 'hello word!'
done
