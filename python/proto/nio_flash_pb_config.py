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
# nio_flash_pb_config.py : [file description]
#

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

import argparse
import os
import nio_flash_pb2
import sys


def pb_file_generator(name, string):
    basic_dir = os.path.split(os.path.realpath(__file__))[0] + "/pb/"
    if not os.path.exists(basic_dir):
        os.makedirs(basic_dir)
    file_path = basic_dir + name+".pb"
    print(file_path)
    try:
        f = open(file_path, "w+")
        f.write(string)
        f.close()
    except IOError:
        print("Could not open file")


def mazu_pb_set():
    component_config = nio_flash_pb2.Configure()
    name = "mazu"
    component_config.target_name = name
    component_config.lib_name = "/lib/libmazu_flash_core.so"

    flashpackage = component_config.flash_package.add()
    flashpackage.name = "imu"
    flashpackage2 = component_config.flash_package.add()
    flashpackage2.name = "isp"
    flashpackage3 = component_config.flash_package.add()
    flashpackage3.name = "gnss"
    flashpackage4 = component_config.flash_package.add()
    flashpackage4.name = "svc"
    flashpackage5 = component_config.flash_package.add()
    flashpackage5.name = "switch"

    pb_file_generator(name, str(component_config))


def imu_pb_set():
    component_config = nio_flash_pb2.Configure()
    name = "imu"
    component_config.target_name = name
    component_config.lib_name = ""
    flashpackage = component_config.flash_package.add()
    flashpackage.name = name
    flashpackage.software_version = "AG040_V3.14_150"
    flashpackage.hardware_version = "040"

    flashpackage = component_config.flash_package.add()
    flashpackage.name = name
    flashpackage.software_version = "AG072_V3.05_703"
    flashpackage.hardware_version = "072"

    pb_file_generator(name, str(component_config))


def isp_pb_set():
    component_config = nio_flash_pb2.Configure()
    name = "isp"
    component_config.target_name = name
    component_config.lib_name = ""
    flashpackage = component_config.flash_package.add()
    flashpackage.name = name
    flashpackage.software_version = "20220310202203102026NIO_MAZU_DVR"
    pb_file_generator(name, str(component_config))


def svc_pb_set():
    component_config = nio_flash_pb2.Configure()
    name = "svc"
    component_config.target_name = name
    component_config.lib_name = ""
    flashpackage = component_config.flash_package.add()
    flashpackage.name = "svc_front"
    flashpackage.software_version = "8"
    flashpackage2 = component_config.flash_package.add()
    flashpackage2.name = "svc_back"
    flashpackage2.software_version = "8"
    flashpackage3 = component_config.flash_package.add()
    flashpackage3.name = "svc_right"
    flashpackage3.software_version = "8"
    flashpackage4 = component_config.flash_package.add()
    flashpackage4.name = "svc_left"
    flashpackage4.software_version = "8"
    pb_file_generator(name, str(component_config))


def switch_pb_set():
    component_config = nio_flash_pb2.Configure()
    name = "switch"
    component_config.target_name = name
    component_config.lib_name = ""
    flashpackage = component_config.flash_package.add()
    flashpackage.name = "switch_1"
    flashpackage.software_version = "1.0.6"
    flashpackage = component_config.flash_package.add()
    flashpackage.name = "switch_2"
    flashpackage.software_version = "1.0.6"
    pb_file_generator(name, str(component_config))


def gnss_pb_set():
    component_config = nio_flash_pb2.Configure()
    name = "gnss"
    component_config.target_name = name
    component_config.lib_name = ""
    flashpackage = component_config.flash_package.add()
    flashpackage.name = "gnss_main"
    flashpackage.software_version = "LG69TAINR01A04V01"
    flashpackage = component_config.flash_package.add()
    flashpackage.name = "gnss_sub"
    flashpackage.software_version = "LG69TAJNR01A04V01"
    pb_file_generator(name, str(component_config))


# def parse_args():
#     parser = argparse.ArgumentParser(description="did_cmd")
#     parser.add_argument("--soc_ip",
#                         type=str,
#                         default="10.42.0.21",
#                         help="Default cmd on soc1, def through soc_ip")
#     parser.add_argument("-s",
#                         "--sales_region",
#                         type=str,
#                         default="CN",
#                         help="sales_region current option: CN, EU")
#     parser.add_argument(
#         "-v",
#         "--vehicle_info",
#         type=str,
#         default="Force",
#         required=True,
#         help="vehicle_type_info current:Force, Gemini, Pegasus")
#     args = parser.parse_args()
#     return args
if __name__ == "__main__":
    # args = parse_args()
    mazu_pb_set()
    imu_pb_set()
    isp_pb_set()
    svc_pb_set()
    gnss_pb_set()
    switch_pb_set()
