include(FetchContent)

FetchContent_Declare(
    googlebenchmark
    URL https://github.com/google/benchmark/archive/afa23b7699c17f1e26c88cbf95257b20d78d6247.zip
    EXCLUDE_FROM_ALL)

FetchContent_MakeAvailable(googlebenchmark)

add_executable(openjph-benchmark
    wavelet_benchmark.cc
)

 message(CMAKE_SYSTEM_PROCESSOR="${CMAKE_SYSTEM_PROCESSOR}")

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    target_link_libraries(openjph-benchmark PUBLIC GTest::gtest_main benchmark::benchmark openjph openjph-wavelet-general openjph-wavelet-avx512)
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
    target_link_libraries(openjph-benchmark PUBLIC GTest::gtest_main benchmark::benchmark openjph openjph-wavelet-general openjph-wavelet-neon)
else()
    target_link_libraries(openjph-benchmark PUBLIC GTest::gtest_main benchmark::benchmark openjph openjph-wavelet-general)
endif()

