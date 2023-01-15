cmake_minimum_required(VERSION 2.6)
project(monitor)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(monitor ${SOURCES})

set_property(TARGET monitor PROPERTY CXX_STANDARD 17)
target_link_libraries(monitor ${CURSES_LIBRARIES})
# TODO: Run -Werror in CI.
target_compile_options(monitor PRIVATE -Wall -Wextra)

# enable debugger own
# -O0 = optimization level 0 = turn off optimizations = all debugging info
# -ggdb = g*** debugging information format gdb = debugger for gcc
# target_compile_options(monitor PRIVATE -Wall -Wextra -O0 -ggdb)

# enable debugger according udacity mentor
set( CMAKE_CXX_FLAGS "-g " )