cmake_minimum_required(VERSION 3.0)
project(JenErator)

set(CMAKE_CXX_STANDARD 17)
if (UNIX)
    link_libraries(stdc++fs)
endif ()
add_subdirectory(jen)