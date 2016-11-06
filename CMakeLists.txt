cmake_minimum_required(VERSION 2.8)
project(wano CXX)

# Clang and GCC Setup
if(CMAKE_CXX_COMPILER_ID MATCHES "(Clang)|(GNU)")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX14)
    if(COMPILER_SUPPORTS_CXX14)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -stdlib=libc++")
    else()
        message(STATUS "Your compiler (${CMAKE_CXX_COMPILER}) does not support C++14.")
    endif()
    
    add_compile_options("-Wfatal-errors")
endif()

# Get dependencies
if(WIN32)
    find_path(CURSES_INCLUDE pdcurses.lib HINTS lib)
    find_library(CURSES_LIBRARIES pdcurses HINTS lib)
    include_directories(${CURSES_INCLUDE})
else()
    find_package(Curses REQUIRED)
endif()

add_subdirectory(curses_ui)
add_subdirectory(wano)