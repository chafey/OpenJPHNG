add_executable(openjph-wavelet-neon-test 
    reversible_vertical_step_unittest.cc
    )

target_link_libraries(openjph-wavelet-neon-test PUBLIC GTest::gtest_main openjph openjph-wavelet-general openjph-wavelet-neon)

include (GoogleTest)

gtest_discover_tests(openjph-wavelet-neon-test) # Runs GTest with CTest