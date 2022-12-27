#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define SLAVE_ADDR 0x51

int i2c_write_bytes(int fd, unsigned short addr, unsigned char *data, int len) {
  unsigned char *data_wr = NULL;
  int ret = -1;

  // data_wr =
  malloc(len + 2);
  // if (!data_wr) {
  //   printf("%s, malloc failed!\n", __func__);
  //   return -1;
  // }

  data_wr[0] = addr / 0xff;
  data_wr[1] = addr % 0xff;
  memcpy(&data_wr[2], data, len);

  ioctl(fd, I2C_SLAVE, SLAVE_ADDR);
  ioctl(fd, I2C_TIMEOUT, 1);
  ioctl(fd, I2C_RETRIES, 1);

  ret = write(fd, data_wr, len + 2);
  if (ret < 0) {
    printf("%s, write failed, ret: 0x%x\n", __func__, ret);
    return ret;
  }

  printf("%s, write ok, num: %d\n", __func__, ret);

  if (data_wr != NULL) {
    free(data_wr);
    data_wr = NULL;
  }

  return ret;
}

int i2c_read_bytes(int fd, unsigned short addr, unsigned char *data, int len) {
  unsigned char addr_slave[2] = {0};
  int ret = -1;

  ioctl(fd, I2C_SLAVE, SLAVE_ADDR);
  ioctl(fd, I2C_TIMEOUT, 1);
  ioctl(fd, I2C_RETRIES, 1);

  addr_slave[0] = addr / 0xff;
  addr_slave[1] = addr % 0xff;

  ret = write(fd, addr_slave, 2);
  if (ret < 0) {
    printf("%s, write failed, ret: 0x%x\n", __func__, ret);
    return ret;
  }

  ret = read(fd, data, len);
  if (ret < 0) {
    printf("%s, read failed, ret: 0x%x\n", __func__, ret);
    return ret;
  }

  printf("%s, read ok, num: %d\n", __func__, ret);

  return ret;
}

int arr_show(unsigned char *data, int len) {
  int i = 0;

  for (i = 0; i < len; i++) {
    printf("data[%d]: 0x%x\n", i, data[i]);
  }

  return 0;
}

void usage(void) {
  printf("xxx -r addr len\n");
  printf("xxx -w addr data1 data2 ...\n");
}

int main(int argc, char *argv[]) {
  int opt;
  int fd = -1;

  unsigned short addr;
  unsigned char buf[256] = {0};
  int len = 0;
  int i = 0;

  if (argc < 4) {
    usage();
    return -1;
  }

  fd = open("/dev/i2c-0", O_RDWR);
  if (fd < 0) {
    printf("%s, open failed!\n", __func__);
    return -1;
  }

  while ((opt = getopt(argc, argv, "w:r:")) != -1) {
    printf("optarg: %s\n", optarg);
    printf("optind: %d\n", optind);
    printf("argc: %d\n", argc);
    printf("argv[optind]: %s\n", argv[optind]);

    addr = (unsigned short)strtol(optarg, NULL, 0);
    printf("addr: %d\n", addr);
    switch (opt) {
      case 'w':
        for (len = 0; optind < argc; optind++, len++) {
          buf[len] = (unsigned char)strtol(argv[optind], NULL, 0);
        }
        printf("len: %d\n", len);

        i2c_write_bytes(fd, addr, buf, len);
        break;
      case 'r':
        len = (unsigned int)strtol(argv[optind], NULL, 0);
        printf("len: %d\n", len);

        i2c_read_bytes(fd, addr, buf, len);

        arr_show(buf, len);
        break;
      default:
        printf("Invalid parameter!\n");
        usage;
        break;
    }
  }
  close(fd);

  return 0;
}