add_executable(openjph-wavelet-general-test forward-reversible_test.cpp)

target_link_libraries(openjph-wavelet-general-test PUBLIC gtest gtest_main openjph-wavelet-general)

include (GoogleTest)

gtest_discover_tests(openjph-wavelet-general-test) # Runs GTest with CTest