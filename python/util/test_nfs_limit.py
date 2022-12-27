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
# test_nfs_limit.py : [file description]
#


import time
import argparse
import threading
import subprocess


def parse_args():
    parser = argparse.ArgumentParser(description="did_cmd")
    parser.add_argument("-t",
                        "--target_dir",
                        type=str,
                        default="/nfs/s1/nio",
                        help="target dir for nfs test")

    parser.add_argument("-s",
                        "--source_dir",
                        type=str,
                        default="/nio",
                        help="target dir for nfs test")

    parser.add_argument("-p",
                        "--package_size_mb",
                        type=int,
                        default=100,
                        help="package_size_mb")

    parser.add_argument("-n",
                        "--number_of_file",
                        type=int,
                        default=10,
                        help="number_of_file")
    parser.add_argument("-c",
                        "--cycle_times",
                        type=int,
                        default=10,
                        help="cycle_times")

    args = parser.parse_args()
    return args


def run_cmd(cmd):
    process = subprocess.Popen([cmd], shell=True,
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    ret = process.returncode
    return [ret, stdout.decode('utf-8', 'replace'), stderr.decode('utf-8', 'replace')]


class NfsTest(object):
    def __init__(self, args):
        self.target_dir = args.target_dir
        self.source_dir = args.source_dir
        self.fils_nums = args.number_of_file
        self.cycle_times = args.cycle_times
        self.file_size_mb = args.package_size_mb
        self.total_file_size_mb = self.fils_nums * self.file_size_mb
        self.file_base_name = "nfs_test_file"
        self.file_name_list = []

    def create_file(self, file_path):
        cmd = "sudo dd if=/dev/urandom of=" + \
            "{} bs=1k count={}k".format(file_path, self.file_size_mb)
        run_cmd(cmd)

    def delete_file(self, file_dir):
        cmd = "rm -rf {}/{}*".format(file_dir, self.file_base_name)
        run_cmd(cmd)
        # os.system('sync')
        # os.system('echo 3 > /proc/sys/vm/drop_caches')
        pass

    def creat_local_files(self):
        thread_list = []
        self.delete_file(self.source_dir)
        start_time = time.clock_gettime(0)
        self.file_name_list = []
        for i in range(self.fils_nums):
            file_name = self.file_base_name + str(i)
            self.file_name_list.append(file_name)
            file_path = self.source_dir + "/" + file_name

            thread_list.append(threading.Thread(
                target=self.create_file, args=(file_path,)))

        for task in thread_list:
            task.start()
        for task in thread_list:
            task.join()
        end_time = time.clock_gettime(0)
        time_interval = end_time - start_time
        speed = self.total_file_size_mb / time_interval

        print("creat_local_files done, time used:{}, average speed:{} mb/s ".format(time_interval, speed))

    def copy_file(self, file_name):
        cmd = "cp {}/{} {}/{}".format(self.source_dir,
                                      file_name, self.target_dir, file_name)
        run_cmd(cmd)

    def copy_to_target_dir(self):
        thread_list = []
        self.delete_file(self.target_dir)

        start_time = time.clock_gettime(0)
        for name in self.file_name_list:
            thread_list.append(threading.Thread(
                target=self.copy_file, args=(name,)))
        for task in thread_list:
            task.start()
        for task in thread_list:
            task.join()
        end_time = time.clock_gettime(0)
        time_interval = end_time - start_time
        speed = self.total_file_size_mb / time_interval
        print("copy_to_target_dir done, time used:{}, average speed:{} mb/s ".format(time_interval, speed))

    def check_file(self, filename):
        cmd = "md5sum {}/{}".format(self.source_dir, filename)
        res_local = run_cmd(cmd)
        cmd = "md5sum {}/{}".format(self.target_dir, filename)
        res_target = run_cmd(cmd)
        if res_local[1][:32] != res_target[1][:32]:
            print("target {} different from local".format(filename))
        else:
            pass

    def check_target_dir(self):
        thread_list = []
        for name in self.file_name_list:
            thread_list.append(threading.Thread(
                target=self.check_file, args=(name,)))

        for task in thread_list:
            task.start()
        for task in thread_list:
            task.join()
        print("check_target_dir done........")


if __name__ == '__main__':
    args = parse_args()
    nfs = NfsTest(args)

    while(1):

        nfs.creat_local_files()
        nfs.copy_to_target_dir()
        nfs.check_target_dir()
