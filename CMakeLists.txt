cmake_minimum_required(VERSION 3.4)
project(project2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -Wall -std=gnu++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wmissing-field-initializers -Wctor-dtor-privacy	-Wnon-virtual-dtor -Wstrict-null-sentinel -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Weffc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-effc++")

find_package(PkgConfig)
pkg_check_modules(GLOG REQUIRED libglog)


# assume that libs have already been built
include_directories(
        ${CMAKE_SOURCE_DIR}/src

        ${CMAKE_SOURCE_DIR}/bridge/include

        ${GLOG_INCLUDE_DIRS}
)

link_directories(
        ${CMAKE_SOURCE_DIR}/bridge/lib
        ${GLOG_LIBRARY_DIRS}
)

add_subdirectory(src)