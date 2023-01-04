
add_library(sensor sensor.c)
target_include_directories(sensor INTERFACE ./)

# pull in common dependencies
target_link_libraries(sensor pico_stdlib hardware_pwm)

## usb-serial enable
#pico_enable_stdio_usb(prail_signal 1)
#pico_enable_stdio_uart(prail_signal 0)
