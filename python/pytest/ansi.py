#!/usr/bin/env python3
# -*- coding:utf-8 -*-

# Copyright (c) 2021, NIO Inc. All rights reserved.
#
# Any use, reproduction, distribution, and/or transfer of this file is strictly
# prohibited without the express written permission of the current copyright
# owner.
#
# Any licensed derivative work must retain this notice.
#

class TerminalColors():
    """Common terminal colors"""
    BLACK = "\033[0;30m"
    RED = "\033[0;31m"
    GREEN = "\033[0;32m"
    YELLOW = "\033[0;33m"
    BLUE = "\033[0;34m"
    PURPLE = "\033[0;35m"
    CYAN = "\033[0;36m"
    WHITE = "\033[0;37m"

    BOLD_BLACK = "\033[1;30m"
    BOLD_RED = "\033[1;31m"
    BOLD_GREEN = "\033[1;32m"
    BOLD_YELLOW = "\033[1;33m"
    BOLD_BLUE = "\033[1;34m"
    BOLD_PURPLE = "\033[1;35m"
    BOLD_CYAN = "\033[1;36m"
    BOLD_WHITE = "\033[1;37m"

    NONE = "\033[0m"

    def __str__(self):
        return "{:s}".format(self.value)

    @staticmethod
    def error(msg, color=RED):
        """Print error message

        Args:
            msg (str) : Message to print
            color (str) : Message color (default RED)
        """
        print(color + msg + TerminalColors.NONE)

    @staticmethod
    def success(msg, color=GREEN):
        """Print success message

        Args:
            msg (str) : Message to print
            color (str) : Message color (default GREEN)
        """
        print(color + msg + TerminalColors.NONE)

    @staticmethod
    def status(msg, color=YELLOW):
        """Print status message

        Args:
            msg (str) : Message to print
            color (str) : Message color (default YELLOW)
        """
        print(color + msg + TerminalColors.NONE)

class CursorNavigation():
    """Cursor navigation"""
    START_OF_LINE = "\033[G"
    HOME = "\033[H"
    CLEAR_LINE = "\033[2K"

    def __str__(self):
        return "{:s}".format(self.value)
