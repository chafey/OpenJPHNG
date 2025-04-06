add_library(openjph)

target_include_directories(openjph PUBLIC 
  "${PROJECT_SOURCE_DIR}/include/")

target_sources(openjph PRIVATE
  line_buf.cc
  message.cc
)

add_subdirectory(wavelet)