#include <stdio.h>
#include <string.h>
#include <zlib.h>
#include <fstream>
#include <iostream>
#include <string>

// #include "zlib.h"
static bool gzip_compress(const std::string &original_str, std::string &str) {
  z_stream d_stream = {0};
  if (Z_OK != deflateInit2(&d_stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
                           MAX_WBITS + 16, 9, Z_DEFAULT_STRATEGY)) {
    return false;
  }
  uLong len = compressBound(original_str.size());
  unsigned char *buf = (unsigned char *)malloc(len);
  if (!buf) {
    return false;
  }
  d_stream.next_in = (unsigned char *)(original_str.c_str());
  d_stream.avail_in = original_str.size();
  d_stream.next_out = buf;
  d_stream.avail_out = len;
  deflate(&d_stream, Z_SYNC_FLUSH);
  deflateEnd(&d_stream);
  str.assign((char *)buf, d_stream.total_out);
  free(buf);
  return true;
}
static void gzip_uncompress(const std::string &original_str, std::string &str) {
  unsigned char buf[102400] = "";
  uLong len = 102400;
  z_stream d_stream = {0};
  int res = inflateInit2(&d_stream, MAX_WBITS + 16);
  d_stream.next_in = (unsigned char *)(original_str.c_str());
  d_stream.avail_in = original_str.size();
  d_stream.next_out = buf;
  d_stream.avail_out = len;
  inflate(&d_stream, Z_SYNC_FLUSH);
  inflateEnd(&d_stream);
  str.assign((char *)buf, d_stream.total_out);
}
/* Uncompress gzip data */

/* zdata 数据 nzdata 原数据长度 data 解压后数据 ndata 解压后长度 */

int gzdecompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata) {
  int err = 0;
  z_stream d_stream = {0}; /* decompression stream */
  static char dummy_head[2] = {
      0x8 + 0x7 * 0x10,
      (((0x8 + 0x7 * 0x10) * 0x100 + 30) / 31 * 31) & 0xFF,
  };
  d_stream.zalloc = NULL;
  d_stream.zfree = NULL;
  d_stream.opaque = NULL;
  d_stream.next_in = zdata;
  d_stream.avail_in = 0;
  d_stream.next_out = data;
  //只有设置为MAX_WBITS + 16才能在解压带header和trailer的文本
  if (inflateInit2(&d_stream, MAX_WBITS + 16) != Z_OK) {
    return -1;
  }
  while (d_stream.total_out < *ndata && d_stream.total_in < nzdata) {
    d_stream.avail_in = d_stream.avail_out = 1; /* force small buffers */
    if ((err = inflate(&d_stream, Z_NO_FLUSH)) == Z_STREAM_END) {
      break;
    }
    if (err != Z_OK) {
      if (err == Z_DATA_ERROR) {
        d_stream.next_in = (Bytef *)dummy_head;
        d_stream.avail_in = sizeof(dummy_head);
        if ((err = inflate(&d_stream, Z_NO_FLUSH)) != Z_OK) {
          return -1;
        }
      } else {
        return -1;
      }
    }
  }
  if (inflateEnd(&d_stream) != Z_OK) {
    return -1;
  }
  *ndata = d_stream.total_out;
  return 0;
}

int main() {
  std::string str;
  std::string res;
  std::fstream ifs("./1.txt");
  if (!ifs) {
    return -1;
  }
  std::string line;
  while (!ifs.eof()) {
    ifs >> line;
    if (!line.empty()) {
      str += line;
    }
    line.clear();
  }
  ifs.close();
  std::cout << str << std::endl;
  std::cout << "size = " << str.size() << std::endl;
  gzip_compress(str, res);
  std::cout << "compress size = " << res.size() << std::endl;
  std::cout << "compress ratio = " << (1.0 * res.size() / str.size()) * 100
            << "%" << std::endl;
  unsigned char buf[102400] = "";
  uLong len = 102400;
  gzdecompress((unsigned char *)(res.c_str()), res.size(), buf, &len);
  std::string str1((char *)buf, len);
  std::cout << "size1 = " << str1.size() << std::endl;
  std::cout << "str1 = " << str1 << std::endl;

  gzip_uncompress(res, str);
  std::cout << "original str = " << str << std::endl;
  std::cout << "size = " << str.size() << std::endl;

  return 0;
}
