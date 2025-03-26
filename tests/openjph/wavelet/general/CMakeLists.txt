add_executable(openjph-wavelet-general-test 
    reversible_forward_transform_unittest.cc
    reversible_vertical_step_t_unittest.cc
    )

target_link_libraries(openjph-wavelet-general-test PUBLIC GTest::gtest_main openjph openjph-wavelet-general)

include (GoogleTest)

gtest_discover_tests(openjph-wavelet-general-test) # Runs GTest with CTest