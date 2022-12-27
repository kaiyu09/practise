
import time
import os
import _thread

filepath = "/nfs/s1/nio"


def creatfile(filename):
    print(f'Start craet file:{filename} >>>>>>>>>>>>>>>>>')
    os.chdir(filepath)
    cmd = "sudo dd if=/dev/urandom of="+f"{filename} bs=1M count=100"
    os.system(cmd)


def tarfile(filename):
    os.chdir(filepath)
    print(f'Start tar file:{filename} >>>>>>>>>>>>>>>>>')
    # du -a > /dev/null
    cmd = 'tar -zcf '+f'{filename}.tar.gz {filename}'
    os.system(cmd)


def detarfile(filename):
    os.chdir(filepath)
    print(f'Start detar file:{filename} >>>>>>>>>>>>>>>>>')
    cmd = 'cd '+filepath
    os.system(cmd)
    cmd = 'tar -zxf '+f'{filename}.tar.gz '
    os.system(cmd)


def readfile(filename):
    os.chdir(filepath)
    print(f'Start read file:{filename} >>>>>>>>>>>>>>>>>')
    f = open(filename)


def start_thread():
    try:
        for i in range(1, 50):
            filename = f'nfs_test{i}'
            _thread.start_new_thread(creatfile, (filename,))
        time.sleep(100)
        for i in range(1, 50):
            filename = f'nfs_test{i}'
            _thread.start_new_thread(readfile, (filename,))
    except:
        print("Error:can't start thread")


def readPara():
    for i in range(1000000000):
        os.chdir(filepath)
        print('Read paremeter file >>>>>>>>>>>>>>>>>>>>>>')
        with open('test.txt', 'r') as f:
            print(f.read())
        time.sleep(1)


def deletefile():
    print('start delete file >>>>>>>>>>>>>>>>>>>>>>')
    cmd = 'rm nfs_test*'
    os.system(cmd)


if __name__ == '__main__':
    while(1):
        # _thread.start_new_thread(readPara, ())
        start_thread()
        time.sleep(30)
        deletefile()
