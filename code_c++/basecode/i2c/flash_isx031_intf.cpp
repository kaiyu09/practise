#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <string>

static int i2c_transfer(int fd, uint16_t slave_addr, uint8_t* master_data,
                        uint16_t master_size, uint8_t* read_data,
                        uint16_t read_size);

static int i2c_transfer(int fd, uint16_t slave_addr, uint8_t* master_data,
                        uint16_t master_size, uint8_t* read_data,
                        uint16_t read_size) {
  struct i2c_rdwr_ioctl_data data;
  int ret = -1;

  if (!master_data) return -1;
  data.nmsgs = 2;
  data.msgs = (struct i2c_msg*)malloc(data.nmsgs * sizeof(struct i2c_msg));
  if (data.msgs == NULL) {
    return -1;
  }
  data.msgs[0].len = master_size;
  data.msgs[0].addr = slave_addr;
  data.msgs[0].flags = 0;
  data.msgs[0].buf = master_data;

  data.msgs[1].len = read_size;
  data.msgs[1].addr = slave_addr;
  data.msgs[1].flags = 1;
  data.msgs[1].buf = read_data;

  ret = ioctl(fd, I2C_RDWR, &data);
  if (ret < 0) {
    printf("i2c_transfer failed! ret: %d\n", ret);
    free(data.msgs);
    return -1;
  }
  free(data.msgs);
  return 0;
}

int main() {
  int fd = -1;
  fd = open("/dev/i2c-0", O_RDWR);
  if (fd < 0) {
    printf("%s, open failed!\n", __func__);
    return -1;
  }
  uint16_t slave_addr = 0x6d;

  uint8_t master_data[] = {0x33, 0x47, 0x03, 0x00, 0x00,
                           0x00, 0x01, 0x00, 0x80, 0xfe};
  uint16_t master_size = sizeof(master_data);
  uint8_t read_data[256] = {0};
  uint16_t read_size = 8;

  i2c_transfer(fd, slave_addr, master_data, master_size, read_data, read_size);

  std::string res_str((char*)&read_data[0], 6);
  printf("res_str:%s\n", res_str.c_str());

  uint8_t cmd_data[] = {0x33, 0x51, 0x07, 0x0c, 0x00, 0x00,
                        0x00, 0x02, 0x00, 0x00, 0x99};
  uint16_t cmd_size = sizeof(cmd_data);
  cmd_data[3] = read_data[3];
  cmd_data[10] = read_data[5] + 0x16;
  uint8_t read_data_sec[256] = {0};
  uint16_t read_size_sec = 250;

  i2c_transfer(fd, slave_addr, cmd_data, cmd_size, read_data_sec,
               read_size_sec);

  std::string date_str((char*)&read_data_sec[111], 8);
  std::string version_str((char*)&read_data_sec[127], 4);

  printf("date:%s\n", date_str.c_str());
  printf("version:%s\n", version_str.c_str());
}
