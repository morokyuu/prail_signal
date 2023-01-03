cmake_minimum_required(VERSION 3.13)

add_executable(test_status)

target_sources(test_status PUBLIC ${CMAKE_CURRENT_LIST_DIR}/test_status.c)

# pull in common dependencies
#target_link_libraries(test_status)



