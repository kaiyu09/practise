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

import argparse
import json
import shutil
import os

def copy_target_file(testfiles,filespath,url,allurepath,region,targetproject,node):
    try:
        for targetfile in testfiles:
            if "container" in targetfile:
                pass
            else:
                file = "{}/{}".format(filespath,targetfile)
                with open(file,"r") as f:
                    content = json.load(f)

                jenkinsurl = {"links": [{"type": "link", "url": "{}".format(url), "name": "{}".format(url)}]}
                description = {"description": "Region: {}\n{}\nNode: {}".format(region,targetproject,node)}
                if content['status'] == "passed":
                    content.update(jenkinsurl)
                    content.update(description)
                    with open(file, "w") as f:
                        json.dump(content, f)
                        copyfile = file
                    continue
                else:
                    content.update(jenkinsurl)
                    content.update(description)
                    with open(file,"w") as f:
                        json.dump(content,f)
                        copyfile = file
                    break
        print(copyfile)
        shutil.copy(r'{}'.format(copyfile),r'{}'.format(allurepath))
    except Exception:
        raise ValueError("case result No targetfile")
if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--report_path', default=None)
    parser.add_argument('--url', default=None)
    parser.add_argument('--report_target', default=None)
    parser.add_argument('--region', default=None)
    parser.add_argument('--targetproject', default=None)
    parser.add_argument('--node', default=None)
    args = parser.parse_args()
    folder = args.report_path
    url = args.url
    file = args.report_target
    region = args.region
    targetproject = args.targetproject
    node = args.node
    folder_content = os.listdir(folder)
    copy_target_file(folder_content,folder,url,file,region,targetproject,node)
