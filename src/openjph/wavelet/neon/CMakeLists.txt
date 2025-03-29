#if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x84_64")
#  add_definitions(-DX84_64_SPECIFIC_CODE)
  add_library(openjph-wavelet-neon)

  target_include_directories(openjph-wavelet-neon PUBLIC 
    "${PROJECT_SOURCE_DIR}/include/")

  target_sources(openjph-wavelet-neon PRIVATE
    reversible_forward_vertical_step.cc
  )
  #target_compile_options(openjph-wavelet-avx512 PRIVATE -march=native)
#endif()


