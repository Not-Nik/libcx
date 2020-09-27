cmake_minimum_required(VERSION 3.17)
project(cx C)

set(CMAKE_C_STANDARD 99)

add_library(cx lib/cx.c lib/cx.h)
target_include_directories(cx PUBLIC lib)

add_library(cx2 lib/cx2.c lib/cx2.h)
target_include_directories(cx2 PUBLIC lib)

add_executable(cx-test test/test.c)
target_link_libraries(cx-test cx)

add_executable(cx2-test test/test2.c)
target_link_libraries(cx2-test cx2)
