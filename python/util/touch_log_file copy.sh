#!/bin/bash

echo "create /nio/logs/latest/* continue"

for ((count = 1; count <= 500; count++)); do

  file_name=$(echo $RANDOM | md5sum | cut -c 1-32)
  echo $file_name
  file="/nio/logs/latest/$file_name"
  echo $file
  sudo touch $file
  echo $?

  intervel=$(($RANDOM % 5))
  avg_exec_time=$(echo "scale=2; $intervel/100" | bc)
  sleep $avg_exec_time

done
exit
