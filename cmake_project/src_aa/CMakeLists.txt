add_library(aa_shared SHARED aa_test.cpp)
target_include_directories(aa_shared PUBLIC .)

# add_executable(aa_exec aa_test.cpp)
# target_include_directories(aa_exec PUBLIC .)

add_library(aa_object OBJECT aa_test.cpp)
add_compile_options(-no-pie)
target_include_directories(aa_object PUBLIC .)

add_library(aa_static STATIC aa_test.cpp)
target_include_directories(aa_static PUBLIC .)
