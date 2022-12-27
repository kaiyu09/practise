
# add_library(cc_shared SHARED cc_test.cpp)
# target_include_directories(cc_shared PUBLIC .)
# # add_compile_options(-fPIC)
# target_link_libraries(cc_shared PUBLIC

# bb_shared
# aa_static)
# # $<TARGET_OBJECTS:aa_object>)




add_executable(cc_exec cc_test.cpp)
target_include_directories(cc_exec PUBLIC .)
target_link_libraries(cc_exec PUBLIC
aa_shared
bb_shared
)
# aa_shared)
# $<TARGET_OBJECTS:aa_object>)


