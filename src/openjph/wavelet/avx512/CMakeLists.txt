
add_library(openjph-wavelet-avx512)

target_include_directories(openjph-wavelet-avx512 PUBLIC 
  "${PROJECT_SOURCE_DIR}/include/")

target_sources(openjph-wavelet-avx512  PRIVATE
  reversible_forward_vertical_step.cc
)
target_compile_options(openjph-wavelet-avx512 PRIVATE -march=native)