add_executable(openjph-wavelet-general-test reversible-forward-transform_unittest.cpp)

target_link_libraries(openjph-wavelet-general-test PUBLIC GTest::gtest_main openjph-wavelet-general)

include (GoogleTest)

gtest_discover_tests(openjph-wavelet-general-test) # Runs GTest with CTest