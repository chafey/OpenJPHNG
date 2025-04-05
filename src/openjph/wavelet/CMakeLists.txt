
add_library(openjph-wavelet)

target_include_directories(openjph-wavelet PUBLIC 
  "${PROJECT_SOURCE_DIR}/include/")

target_sources(openjph-wavelet PRIVATE
  param_atk.cc
)

#target_link_libraries(openjph-wavelet PUBLIC openjph)

add_subdirectory(general)

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    add_subdirectory(avx512)
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
    add_subdirectory(neon)
endif()