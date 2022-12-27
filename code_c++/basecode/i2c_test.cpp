#include <errno.h>
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

#define I2C_ADAPTER "/dev/i2c-0"
#define I2C_DEVICE 0x00

int i2c_ioctl_write(int fd, uint8_t dev, uint8_t regaddr, uint16_t *data,
                    size_t size) {
  int i, j = 0;
  int ret;
  uint8_t *buf;
  // the extra byte is for the regaddr
  size_t buff_size = 1 + size;

  malloc(buff_size);
  //   buf = malloc(buff_size);
  //   if (buf == NULL) {
  //     return -ENOMEM;
  //   }

  buf[j++] = regaddr;
  for (i = 0; i < size / sizeof(uint16_t); i++) {
    buf[j++] = (data[i] & 0xff00) >> 8;
    buf[j++] = data[i] & 0xff;
  }

  struct i2c_msg messages[] = {
      {
          .addr = dev,
          .buf = buf,
          .len = buff_size,
      },
  };

  struct i2c_rdwr_ioctl_data payload = {
      .msgs = messages,
      .nmsgs = sizeof(messages) / sizeof(messages[0]),
  };

  ret = ioctl(fd, I2C_RDWR, &payload);
  if (ret < 0) {
    ret = -errno;
  }

  free(buf);
  return ret;
}

int i2c_ioctl_smbus_write(int fd, uint8_t dev, uint8_t regaddr, uint16_t *data,
                          size_t size) {
  int i, j = 0;
  int ret;
  uint8_t *buf;

  malloc(size);

  //   buf = malloc(size);
  //   if (buf == NULL) {
  //     return -ENOMEM;
  //   }

  for (i = 0; i < size / sizeof(uint16_t); i++) {
    buf[j++] = (data[i] & 0xff00) >> 8;
    buf[j++] = data[i] & 0xff;
  }

  struct i2c_smbus_ioctl_data payload = {
      .read_write = I2C_SMBUS_WRITE,
      .size = I2C_SMBUS_WORD_DATA,
      .command = regaddr,
      .data = (void *)buf,
  };

  ret = ioctl(fd, I2C_SLAVE_FORCE, dev);
  if (ret < 0) {
    ret = -errno;
    goto exit;
  }

  ret = ioctl(fd, I2C_SMBUS, &payload);
  if (ret < 0) {
    ret = -errno;
    goto exit;
  }

exit:
  free(buf);
  return ret;
}

int i2c_write(int fd, uint8_t dev, uint8_t regaddr, uint16_t *data,
              size_t size) {
  unsigned long funcs;

  if (ioctl(fd, I2C_FUNCS, &funcs) < 0) {
    return -errno;
  }

  if (funcs & I2C_FUNC_I2C) {
    return i2c_ioctl_write(fd, dev, regaddr, data, size);
  } else if (funcs & I2C_FUNC_SMBUS_WORD_DATA) {
    return i2c_ioctl_smbus_write(fd, dev, regaddr, data, size);
  } else {
    return -ENOSYS;
  }
}

int parse_args(uint8_t *regaddr, uint16_t *data, size_t size, char *argv[]) {
  char *endptr;
  int i;

  *regaddr = (uint8_t)strtol(argv[1], &endptr, 0);
  if (errno || endptr == argv[1]) {
    return -1;
  }

  for (i = 0; i < size / sizeof(uint16_t); i++) {
    data[i] = (uint16_t)strtol(argv[i + 2], &endptr, 0);
    if (errno || endptr == argv[i + 2]) {
      return -1;
    }
  }

  return 0;
}

void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s regaddr data [data]*\n", argv[0]);
  fprintf(stderr, "  regaddr   The 8-bit register address to write to.\n");
  fprintf(stderr, "  data      The 16-bit data to be written.\n");
  exit(-1);
}

int main(int argc, char *argv[]) {
  uint8_t regaddr;
  uint16_t *data;
  size_t size;
  int fd;
  int ret = 0;

  if (argc < 3) {
    usage(argc, argv);
  }

  size = (argc - 2) * sizeof(uint16_t);
  malloc(size);
  //   if (data == NULL) {
  //     fprintf(stderr, "%s.\n", strerror(ENOMEM));
  //     return -ENOMEM;
  //   }

  if (parse_args(&regaddr, data, size, argv) != 0) {
    free(data);
    usage(argc, argv);
  }

  fd = open(I2C_ADAPTER, O_RDWR | O_NONBLOCK);
  ret = i2c_write(fd, I2C_DEVICE, regaddr, data);
  close(fd);

  if (ret) {
    fprintf(stderr, "%s.\n", strerror(-ret));
  }

  free(data);

  return ret;
}