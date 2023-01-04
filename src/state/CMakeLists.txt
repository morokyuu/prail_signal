
add_library(state state.c)
target_include_directories(state INTERFACE ./)

target_link_libraries(state sensor)


