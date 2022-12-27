
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
# mazu_cmd.py : [file description]
#

import subprocess
import pytest
import logging
# ⽇志级别⼤⼩关系：CRITICAL > ERROR > WARNING > INFO > DEBUG > NOTSET


def func(x):
    logging.debug('This is debug message')
    logging.info('This is info message')
    logging.warning("This is warning message")
    logging.critical("123"*10)

    return x + 1


def f():
    raise SystemExit(1)


def test_mytest():
    with pytest.raises(SystemExit):
        f()

# match的使用


def test_zero_division_match():
    with pytest.raises(ZeroDivisionError, match=".*zero.*") as exceptionInfo:
        100 / 0
    with pytest.raises(ZeroDivisionError, match="zero") as exceptionInfo:
        100 / 0


def run_cmd(cmd):
    """ Run shell command.
    """
    process = subprocess.Popen([cmd], shell=True,
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    ret = process.returncode
    stdout, stderr = process.communicate()

    print(ret)
    print(stdout.decode('utf-8', 'replace'))
    print(stderr.decode('utf-8', 'replace'))
    return [ret, stdout, stderr]


def test_answer():
    assert func(3) == 4
    assert func(4) == 5
    assert func(6) == 7

    cms_str = "ping baidu.com -c 8"
    res = run_cmd(cms_str)
