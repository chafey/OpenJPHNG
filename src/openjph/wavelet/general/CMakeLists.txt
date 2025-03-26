
add_library(openjph-wavelet-general)

target_include_directories(openjph-wavelet-general PUBLIC 
  "${PROJECT_SOURCE_DIR}/include/")

target_sources(openjph-wavelet-general  PRIVATE
  reversible_forward_transform.cc
  reversible_vertical_step.cc
  reversible_horizontal_ana.cc
)
