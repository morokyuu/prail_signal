
add_library(sensor sensor.c)
target_include_directories(sensor INTERFACE ./)

# pull in common dependencies
target_link_libraries(sensor pico_stdlib hardware_pwm)

