
add_subdirectory(wavelet)

add_library(openjph)

target_include_directories(openjph PUBLIC 
  "${PROJECT_SOURCE_DIR}/include/")

target_sources(openjph PRIVATE
  line_buf.cc
)

target_link_libraries(openjph PUBLIC openjph-wavelet-general)