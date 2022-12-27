# 指定cmake版本，只需要指定大版本和小版本即可
cmake_minimum_required(VERSION 3.10)

# 指定项目名称，项目版本号，主要实现语言
project(cmake_kk VERSION 1.0.0 LANGUAGES C CXX)


# # 添加子目录
# add_subdirectory(
#     ./src_aa
#     ./src_bb
#     ./src_cc
# )

# 设置c++ 版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(kkexe kk_test.cpp)

add_subdirectory(src_cc)
add_subdirectory(src_bb)
add_subdirectory(src_aa)
