add_library(SkseExample main.cpp)
set(CMAKE_CXX_STANDARD 23)
target_compile_features(
        SkseExample
        PRIVATE
        cxx_std_23
)

target_link_libraries(SkseExample xse::common skse64::skse64_common skse64::skse64)
