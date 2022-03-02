cmake_minimum_required(VERSION 3.22)

option(SKYRIM_AE "Compile plugin for Skyrim AE" OFF)
option(SKYRIM_SE "Compile plugin for Skyrim SE" OFF)
option(SKYRIM_VR "Compile plugin for Skyrim VR" OFF)

message(INFO "COMPILING FOR SKYRIM AE: ${SKYRIM_AE}")
message(INFO "COMPILING FOR SKYRIM SE: ${SKYRIM_SE}")
message(INFO "COMPILING FOR SKYRIM VR: ${SKYRIM_VR}")

# message(INFO BEFORE)
# return()
# message(INFO AFTER)

if(NOT ${SKYRIM_AE} AND NOT ${SKYRIM_SE} AND NOT ${SKYRIM_VR})
	message(ERROR "Run cmake using one of the build/ .bat files for building Skyrim")
	return()
endif()

add_definitions(-DSKYRIM_AE)

project(
	ExampleProject
	VERSION 1.0.0
	LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
	message(FATAL_ERROR "in-source builds are not allowed")
endif()

macro(set_from_environment VARIABLE)
	if(NOT DEFINED ${VARIABLE} AND DEFINED ENV{${VARIABLE}})
		set(${VARIABLE} $ENV{${VARIABLE}})
	endif()
endmacro()

set_from_environment(Skyrim64Path)
if(NOT DEFINED Skyrim64Path)
	message(FATAL_ERROR "Skyrim64Path is not set")
endif()

option(COPY_OUTPUT "copy the output of build operations to the game directory" OFF)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

add_subdirectory(src)

include(cmake/packaging.cmake)
