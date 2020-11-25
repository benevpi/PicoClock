cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(picoclock)


pico_sdk_init()


add_executable(picoclock
        picoclock.c
        )

# Pull in our (to be renamed) simple get you started dependencies
target_link_libraries(picoclock pico_stdlib hardware_rtc)

# create map/bin/hex file etc.
pico_add_extra_outputs(picoclock)
