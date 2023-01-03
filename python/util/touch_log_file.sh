#!/bin/bash

echo "create /nio/logs/latest/* continue"



for ((count = 1; count <= 50000; count++)); do

  file_name=$(echo $RANDOM | md5sum | cut -c 1-32)

  file="/nio/logs/latest/$file_name"
  echo $file
  dd if=/dev/urandom of=$file bs=1M count=1 &
  echo $?
  tree /nio

  file2="/mnt/data/$file_name"
  echo $file2
  dd if=/dev/urandom of=$file2 bs=1M count=1 &
  echo $?
  tree /mnt/data

  file3="/mnt/model/$file_name"
  echo $file3
  dd if=/dev/urandom of=$file3 bs=1M count=1
  echo $?
  tree /mnt/model

  # intervel=$(($RANDOM % 5))
  # avg_exec_time=$(echo "scale=2; $intervel/100" | bc)
  # sleep $avg_exec_time

done
exit
