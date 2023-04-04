cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(picoEpaper C CXX ASM)
set(CMAKE_C STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_subdirectory(lib)

add_executable(picoEpaper
  main.cpp
)

# This will enable serial output via USB
pico_enable_stdio_usb(picoEpaper 1)

pico_add_extra_outputs(picoEpaper)

target_link_libraries(picoEpaper caleEPD epd_gui_paint epd_fonts)