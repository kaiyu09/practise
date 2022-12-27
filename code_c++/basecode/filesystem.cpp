
#include <cstdint>
#include <experimental/filesystem>
#include <filesystem>
#include <iostream>
#include <map>

namespace fs = std::experimental::filesystem;
int main() {
  std::string a =
      "/mnt/flash/P0228609_ZZ_20220308_fw_cb12787_app_17b31bc8.tar.gz";
  std::string b = "P0228609_ZZ_20220308_fw_cb12787_app_17b31bc8.tar.gz";

  const std::experimental::filesystem::v1::__cxx11::path aaa = (std::experimental::filesystem::v1::__cxx11::path)a;
  const std::experimental::filesystem::v1::__cxx11::path bbb = (std::experimental::filesystem::v1::__cxx11::path)b;
  // if (a>=b){
  //   printf("hhhh");
  // }


  // std::cout << "tmpdir" << std::endl;
  // std::string tmpdir = "/home/nio/tt/kk/yu";
  // std::cout << tmpdir << std::endl;

  // // auto rc = fs::remove_all(kk_dir);
  // // std::cout << rc << std::endl;

  // // auto rc = std::filesystemcreate_directories(kk_dir);
  // // std::cout << rc << std::endl;

  // fs::directory_iterator list(tmpdir);
  // for (auto &iter : list) {
  //   std::cout << iter << std::endl;
  // }

  // auto pathkk = fs::path tmp = fs::temp_directory_path();
  // fs::create_directories(tmp / "abcdef/example");
  // std::uintmax_t n = fs::remove_all(tmp / "abcdef");
  // std::cout << "Deleted " << n << " files or directories\n";
}

// clang-format off
// void copy(const path& from, const path& to) ：目录复制
// path absolute(const path& pval, const path& base = current_path()) ：获取相对于base的绝对路径
// bool create_directory(const path& pval) ：当目录不存在时创建目录
// bool create_directories(const path& pval) ：形如/a/b/c这样的，如果都不存在，创建目录结构
// bool exists(const path& pval) ：用于判断path是否存在
// uintmax_t file_size(const path& pval) ：返回目录的大小
// file_time_type last_write_time(const path& pval) ：返回目录最后修改日期的file_time_type对象
// bool remove(const path& pval) ：删除目录
// uintmax_t remove_all(const path& pval) ：递归删除目录下所有文件，返回被成功删除的文件个数
// void rename(const path& from, const path& to) ：移动文件或者重命名
