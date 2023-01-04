add_executable(prail_signal main.c)

# pull in common dependencies
target_link_libraries(prail_signal pico_stdlib hardware_pwm state)

# usb-serial enable
pico_enable_stdio_usb(prail_signal 1)
pico_enable_stdio_uart(prail_signal 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(prail_signal)


add_subdirectory(state)

