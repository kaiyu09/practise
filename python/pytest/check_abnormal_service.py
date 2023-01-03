import os
import time
import datetime
import argparse
import subprocess


service_list = ["calib-result-mgr", "clock_time_manager", "cpc_service", "dtc_reporter", "fault_manager", "file-upload-mgr", "fota-server", "gnss_imu_service", "heartbeat_trigger", "hw_manager", "log-manager", "mcu_log", "mcu_proxy", "camera_intrinsic_service", "eol_service",
                "calib-post-sale-service", "remote-app-action", "request-router", "sysmon_app", "version-daemon", "preloadlib_service", "ptp4l", "routingmanagerd", "someip-endpoint", "status_monitor", "time-update-client", "tsp-file-mgr", "tsp-msg-mgr", "uds-service", "vehicle-data-service-daemon",]


def run_cmd(cmd):
    process = subprocess.Popen([cmd], shell=True,
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    ret = process.returncode
    return [ret, stdout.decode('utf-8', 'replace'), stderr.decode('utf-8', 'replace')]


password = 'w+G)X8e)M5gwJ.*}wx,X'
soclist = ["1", "2", "3", "4"]
time_str = str(datetime.datetime.now()).replace(" ", "--")
print(file_dir)


for soc_num in soclist:
    for disk in disklist:

        cmd_soc = "ls {}".format(
            disk)
        cmd_host = "sudo sshpass -p '{}' ssh -o StrictHostKeyChecking=no -t root@10.42.0.2{} '{}'".format(
            password, soc_num, cmd_soc)
        # print(cmd_host)+
        res = run_cmd(cmd_host)
