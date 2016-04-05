# ============================================================================ #
# Copyright (C) 2013 RivaSense. All rights reserved.                           #
# ============================================================================ #
#
# Set version based on git information and current state of source directory.
#
# The module defines the following variables:
#   GIT_SOURCE_VERSION - tag based version name
#   GIT_SOURCE_RELEASE - commit based version

find_package(Git)

set(GIT_SOURCE_RELEASE 0.0.0)
set(GIT_SOURCE_VERSION "1-dirty")

if(GIT_FOUND AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git")
  # Try to link version and release to closest annotated tag.
  execute_process(COMMAND ${GIT_EXECUTABLE} describe --dirty
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    OUTPUT_VARIABLE TAG
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET)  
  if(NOT "${TAG}" STREQUAL "")
    string(REGEX MATCHALL "^([^-]+)(-(.+))?$" UNUSED "${TAG}")
    set(GIT_SOURCE_RELEASE "${CMAKE_MATCH_1}")
    if (NOT "${CMAKE_MATCH_3}" STREQUAL "")
      if(NOT "${CMAKE_MATCH_3}" STREQUAL "dirty")
        string(REGEX MATCHALL "^([0-9]+)-(.+)$" UNUSED "${CMAKE_MATCH_3}")
        math(EXPR CMAKE_MATCH_1 "${CMAKE_MATCH_1} + 1")
        set(GIT_SOURCE_VERSION "${CMAKE_MATCH_1}-${CMAKE_MATCH_2}")
      else()
        set(GIT_SOURCE_VERSION "1-${CMAKE_MATCH_3}")
      endif()
    else()
      set(GIT_SOURCE_VERSION 1)
    endif()
  else()
    # No appropriate tag was found: use commit number and hash.
    execute_process(COMMAND ${GIT_EXECUTABLE} rev-list --count HEAD
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      OUTPUT_VARIABLE COUNT
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_QUIET)
    execute_process(COMMAND ${GIT_EXECUTABLE} describe --dirty --always
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      OUTPUT_VARIABLE ID
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_QUIET)
    set(GIT_SOURCE_RELEASE 0.0.0)
    if(NOT "${COUNT}" STREQUAL "")
      math(EXPR COUNT "${COUNT} + 1")
      set(GIT_SOURCE_VERSION "${COUNT}-${ID}")
    else()
      set(GIT_SOURCE_VERSION "1-dirty")
    endif()
  endif()
endif()
