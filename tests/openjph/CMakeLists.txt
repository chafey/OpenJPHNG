add_subdirectory(wavelet)

add_executable(openjph-unittest 
    line_buf_unittest.cc
    mem_fixed_allocator_unittest.cc
    )

target_link_libraries(openjph-unittest PUBLIC GTest::gtest_main openjph )
#openjph-wavelet-general)

include (GoogleTest)

gtest_discover_tests(openjph-unittest) # Runs GTest with CTest