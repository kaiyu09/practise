add_library(bb_shared SHARED bb_test.cpp)
target_include_directories(bb_shared PUBLIC .)
# target_link_libraries(bb_shared PUBLIC aa_shared)

add_library(bb_static STATIC bb_test.cpp)
target_include_directories(bb_static PUBLIC .)
target_link_libraries(bb_static PUBLIC aa_shared)

# add_executable(bb_exec bb_test.cpp)
# target_include_directories(bb_exec PUBLIC .)
# target_link_libraries(bb_exec PUBLIC aa_shared)
