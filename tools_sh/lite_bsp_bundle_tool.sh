#!/bin/bash
# Copyright (c) 2022, NIO Inc. All rights reserved.
#
# Any use, reproduction, distribution, and/or transfer of this file is strictly
# prohibited without the express written permission of the current copyright
# owner.
#
# Any licensed derivative work must retain this notice.
#
# lite_bsp_bundle_tool.sh:
#


# for /tmp  folder  virtual memory
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/" && pwd -P)"
bsp_bundle_path=$script_dir

image_name="A_1_gos0-fs_6_ext4.img"
mountpoint_image="/tmp/bspimg"

s1cfile="images_s1_p3710-10-a01-c01"
s2cfile="images_s2_p3710-10-a01-c01"
s3cfile="images_s3_p3710-10-a01-c01"
s4cfile="images_s4_p3710-10-a01-c01"

delete_app_lib="./home/mazu/app/lib"
delete_app_data="./home/mazu/app/data"


function gen_new_lite_bsp_bundle() {
    disk_space_check
    mount_image
    delete_apps_in_images
    umount_image
    delete_chain_B_partion_flash_config
    resize_target_image
}

function disk_space_check(){
    dist_space_threshold=20
    for ((i=2; i<20; i++)); do
        awk_cmd_mountpoint="NR==""$i"'{print $6}'
        awk_cmd_availspace="NR==""$i"'{print $4}'

        mount_point_name=`df -hl $BASEHOME | awk "$awk_cmd_mountpoint"`
        # echo $mount_point_name
        if [ '/' == $mount_point_name ]; then
            availspace=`df -hl $BASEHOME | awk "$awk_cmd_availspace" | sed 's/G//g' `
            if [ $availspace -lt $dist_space_threshold ]; then
                echo "ERROR::Insufficient disk space: $availspace""G,"" actually need $dist_space_threshold""G needed"
                return $availspace
            fi
            echo "INFO::disk space avail: $availspace""G."
        fi
    done
}

function mount_image() {
    cd $bsp_bundle_path

    mkdir -p $mountpoint_image
    if [ $? -ne 0 ]; then
        echo "ERROR::failed to make dir: $mountpoint_image"
        exit $?
    fi

    mountpoint $mountpoint_image >/dev/null
    if [ $? -eq 0 ]; then
        sudo umount $mountpoint_image >/dev/null
    fi

    sudo mount ./$image_name $mountpoint_image
    if [ $? -ne 0 ]; then
        echo "ERROR::failed to mount: $image_name to $mountpoint_image"
        exit $?
    fi
}


function umount_image() {
    cd $bsp_bundle_path
    mountpoint $mountpoint_image >/dev/null
    if [ $? -eq 0 ]; then
        sudo umount $mountpoint_image >/dev/null
    fi
}


function delete_apps_in_images() {
    cd $mountpoint_image
    sudo rm -rf $delete_app_lib $delete_app_data >/dev/null
    if [ -e $delete_app_lib ]; then
        echo "ERROR::failed to delete: $delete_app_lib "
        exit $?
    fi
    if [ -e $delete_app_data ]; then
        echo "ERROR::failed to delete: $delete_app_data"
        exit $?
    fi
}

function delete_chain_B_partion_flash_config() {
    cd $bsp_bundle_path
    if [ $target_delete_chain == "b" ]; then
        sudo sed -i '/B_/d' ./$s1cfile/642-63710-0010-000_TS2/flash-images/FileToFlash.txt
        sudo sed -i '/B_/d' ./$s2cfile/642-63710-0010-000_TS2/flash-images/FileToFlash.txt
        sudo sed -i '/B_/d' ./$s3cfile/642-63710-0010-000_TS2/flash-images/FileToFlash.txt
        sudo sed -i '/B_/d' ./$s4cfile/642-63710-0010-000_TS2/flash-images/FileToFlash.txt
    fi
}

function resize_target_image() {
    cd $bsp_bundle_path
    e2fsck -f ./$image_name
    resize2fs -M ./$image_name
}

function set_soc_recovery_mode() {
    cd $bsp_bundle_path
    soc_index_arr=(1,2,3,4)
}


function flash_soc_bsp() {
    cd $bsp_bundle_path
    soc_index_arr=(1,2,3,4)
    if echo "${soc_index_arr[@]}" | grep -w $soc_index_flash &>/dev/null; then
        flash_tools="$bsp_bundle_path/images_s$soc_index_flash""_p3710-10-a01-c01/tools/flashtools/bootburn/flash_bsp_images.py"
        soc_bsp_config_file="$bsp_bundle_path/images_s$soc_index_flash""_p3710-10-a01-c01/642-63710-0010-000_TS2"
        echo $flash_tools
        echo $soc_bsp_config_file
        # get cmd key value from imput soc_index
        mcu_reset_index_ip=$(((soc_index_flash+1)/2+145))
        tagra_x_index=$((2-((soc_index_flash)%2)))
    else
        echo "ERROR::wrong soc index, only soc(1,2,3,4) accepted"
        exit
    fi
    res_ping=`ping -c 4 10.42.0.$mcu_reset_index_ip`
    if [[ $(echo $res_ping | grep ' 0% packet loss') == "" ]]; then
        echo "ERROR::Mazu ethernet not connected, tool exit now!"
        exit
    fi
    recovery_mode_cmd=`echo "tegrarecovery x$tagra_x_index on" | nc -w 2 -u -p 53000 10.42.0.$mcu_reset_index_ip 53002`
    reset_cmd=`echo "tegrareset x$tagra_x_index" | nc -w 2 -u -p 53000 10.42.0.$mcu_reset_index_ip 53002`
    echo $recovery_mode_cmd
    echo $reset_cmd
    echo "INFO::Soc$soc_index_flash recovery mode set"
    if [[ $(lsusb | grep NVIDIA) == "" ]]; then
        echo "ERROR::Soc$soc_index_flash usb not connected"
        exit
    fi
    echo "INFO::Soc$soc_index_flash in recovery mode now"
    echo "INFO::flash soc$soc_index_flash bsp ongoing, wait 480s about"
    res_flash_soc="sudo python3 $flash_tools -b p3710-10-a01-c01-s$soc_index_flash -P $soc_bsp_config_file"
    echo $res_flash_soc
    $res_flash_soc
    echo "INFO::flash soc$soc_index_flash bsp finished"
    echo "INFO::Soc$soc_index_flash recovery mode exitting"
    exit_recovery_mode_cmd=`echo "tegrarecovery x$tagra_x_index off" | nc -w 2 -u -p 53000 10.42.0.$mcu_reset_index_ip 53002`
    reset_cmd=`echo "tegrareset x$tagra_x_index" | nc -w 2 -u -p 53000 10.42.0.$mcu_reset_index_ip 53002`
    echo "INFO::Soc$soc_index_flash into recovery mode exited"
}



function show_usage() {
    cat <<EOF
Usage: $0 [options] ...
OPTIONS:
    -d, --delete_chain_config    delete flash conf chain b(only)
    -s, --soc_index_flash        Choose soc_index to flash through usb
    -p, --package_path           Original bsp (filename.tar.gz) bundle path.
    -l, --lite_bsp_bundle        Gen_new_lite_bsp_bundle, delete delete_apps component_in_images
    -h, --help                   Display this help and exit.
EOF
}

function parse_arguments() {
    while [ $# -gt 0 ]; do
        local opt="$1"
        shift
        case "${opt}" in
            -p | --package)
                # target_delete_chain=$1
                exit $?
            ;;
            -s | --package)
                soc_index_flash=$1
                flash_soc_bsp
                exit $?
            ;;
            -h | --help)
                show_usage
                exit 1
            ;;
            -d | --delete_chain_config)
                target_delete_chain=$1
                gen_new_lite_bsp_bundle
                exit 1
            ;;
            *)
                echo "Unknown option: ${opt}"
                exit 2
            ;;
        esac
    done
}

function main() {
    parse_arguments "$@"
}

main "$@"
