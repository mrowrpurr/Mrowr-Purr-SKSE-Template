cmake_minimum_required(VERSION 3.21)

project(TopLevelOfExample)

##################################################################

macro(set_linking_vclib CompilerFlag LinkFlag)
    string(REPLACE "/MDd" "" ${CompilerFlag} "${${CompilerFlag}}")
    string(REPLACE "/MD" "" ${CompilerFlag} "${${CompilerFlag}}")
    string(REPLACE "/MTd" "" ${CompilerFlag} "${${CompilerFlag}}")
    string(REPLACE "/MT" "" ${CompilerFlag} "${${CompilerFlag}}")
    set(${CompilerFlag} "${${CompilerFlag}} ${LinkFlag}")
    message("${CompilerFlag}=${${CompilerFlag}}")
endmacro()

option(STATIC_VCLIB "Linking static VC++ runtime library (/MT or /MTd)." ON)

if(STATIC_VCLIB)
    message("-- Linking static VC++ runtime library (/MT or /MTd): -DSTATIC_VCLIB=ON")

    set_linking_vclib(CMAKE_CXX_FLAGS_DEBUG          "/MTd")
    set_linking_vclib(CMAKE_C_FLAGS_DEBUG            "/MTd")
    set_linking_vclib(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MTd")
    set_linking_vclib(CMAKE_C_FLAGS_RELWITHDEBINFO   "/MTd")
    set_linking_vclib(CMAKE_CXX_FLAGS_RELEASE        "/MT")
    set_linking_vclib(CMAKE_C_FLAGS_RELEASE          "/MT")
    set_linking_vclib(CMAKE_CXX_FLAGS_MINSIZEREL     "/MT")
    set_linking_vclib(CMAKE_C_FLAGS_MINSIZEREL       "/MT")
else()
    message("-- Linking dynamic VC++ runtime library (/MD or /MDd): -DSTATIC_VCLIB=OFF")

    set_linking_vclib(CMAKE_CXX_FLAGS_DEBUG          "/MDd")
    set_linking_vclib(CMAKE_C_FLAGS_DEBUG            "/MDd")
    set_linking_vclib(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MDd")
    set_linking_vclib(CMAKE_C_FLAGS_RELWITHDEBINFO   "/MDd")
    set_linking_vclib(CMAKE_CXX_FLAGS_RELEASE        "/MD")
    set_linking_vclib(CMAKE_C_FLAGS_RELEASE          "/MD")
    set_linking_vclib(CMAKE_CXX_FLAGS_MINSIZEREL     "/MD")
    set_linking_vclib(CMAKE_C_FLAGS_MINSIZEREL       "/MD")
endif()

##################################################################

file(GLOB SSE_COMMON_SRC        common/common/*.h         common/common/*.cpp)
file(GLOB SSE_SKSE64_COMMON_SRC skse64/skse64_common/*.h  skse64/skse64_common/*.cpp)
file(GLOB SSE_SKSE64_SRC        skse64/skse64/*.h         skse64/skse64/*.cpp)

add_library(sse_common        STATIC ${SSE_COMMON_SRC})
add_library(sse_skse64_common STATIC ${SSE_SKSE64_COMMON_SRC})
add_library(sse_skse64        STATIC ${SSE_SKSE64_SRC})

target_include_directories(sse_common PUBLIC common/ skse64/ skse64/xbyak/)
target_compile_options(sse_common PUBLIC /FIcommon/IPrefix.h)
target_compile_definitions(sse_skse64 PRIVATE
        SKSE64_EXPORTS
        RUNTIME
        RUNTIME_VERSION=0x010503E0
        )

target_link_libraries(sse_skse64_common sse_common)
target_link_libraries(sse_skse64 sse_skse64_common)

##################################################################

#project(SkseExample VERSION 0.0.1 LANGUAGES CXX)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#include(compile_definitions)

#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

#add_subdirectory(common)
#add_subdirectory(skse64)
#add_subdirectory(skse64/skse64_common)
#add_subdirectory(skse64/skse64)

#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
add_subdirectory(src)
