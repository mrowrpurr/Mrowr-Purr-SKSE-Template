project(SkseExample VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
add_library(SkseExample SHARED main.cpp)
set(CMAKE_CXX_STANDARD 23)
target_compile_features(
        SkseExample
        PRIVATE
        cxx_std_23
)

target_link_libraries(SkseExample sse_common sse_skse64_common sse_skse64)





#add_library(sse_common        STATIC ${SSE_COMMON_SRC})
#add_library(sse_skse64_common STATIC ${SSE_SKSE64_COMMON_SRC})
#add_library(sse_skse64        STATIC ${SSE_SKSE64_SRC})





#find_package(common CONFIG REQUIRED)
#target_link_libraries(SkseExample PRIVATE xse::common skse64::skse64)

#target_link_libraries(SkseExample PUBLIC xse::common skse64::skse64_common skse64::skse64)
