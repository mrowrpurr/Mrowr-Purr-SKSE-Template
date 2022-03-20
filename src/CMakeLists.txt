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

#find_package(common CONFIG REQUIRED)
#target_link_libraries(SkseExample PRIVATE xse::common skse64::skse64)

target_link_libraries(SkseExample PUBLIC xse::common skse64::skse64_common skse64::skse64)
