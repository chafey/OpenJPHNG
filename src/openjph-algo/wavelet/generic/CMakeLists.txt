
add_library(openjph-algo-wavelet-generic-lib STATIC)

target_include_directories(openjph-algo-wavelet-generic-lib PRIVATE "${PROJECT_SOURCE_DIR}/include/")

target_sources(openjph-algo-wavelet-generic-lib  PRIVATE
    forward-reversible.cpp
)
