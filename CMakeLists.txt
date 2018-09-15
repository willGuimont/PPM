cmake_minimum_required(VERSION 3.7)
project(PPM)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c Pixel.h Pixel.c Draw.h Draw.c Macro.h)

add_executable(PPM ${SOURCE_FILES})