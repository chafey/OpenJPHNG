#if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x84_64")
#  add_definitions(-DX84_64_SPECIFIC_CODE)

  target_sources(openjph PRIVATE
    reversible_forward_vertical_step.cc
  )
  #target_compile_options(openjph-wavelet-avx512 PRIVATE -march=native)
#endif()


