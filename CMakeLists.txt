# ============================================================================ #
# (C) 2016 RivaSense
# ============================================================================ #

project(riva-codec)

# CMake configuration:
cmake_minimum_required(VERSION 2.8)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Set default built type to DEBUG:
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING 
    "Choose the type of build, options are: Debug Release."
    FORCE)
endif()
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release)

# Compiler options:
set(CMAKE_C_FLAGS "-Wall -std=gnu11")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g")
set(CMAKE_C_FLAGS_RELEASE "-Werror -O2 -DNDEBUG -fno-strict-aliasing")

set(CODEC_SOURCE
    src/codec.c src/pdu.c
    src/s1ap/s1ap.c)

# Target:
add_executable(riva-codec "${CODEC_SOURCE}")
