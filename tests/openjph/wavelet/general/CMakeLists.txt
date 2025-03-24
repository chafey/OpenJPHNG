add_executable(openjph-wavelet-general-test forward-reversible_test.cpp)

target_link_libraries(openjph-wavelet-general-test PRIVATE openjph-wavelet-general gtest_main)


# Now simply link against gtest or gtest_main as needed. Eg
#add_executable(example example.cpp)
#target_link_libraries(example gtest_main)
add_test(NAME BasicTest COMMAND openjph-wavelet-general-test)