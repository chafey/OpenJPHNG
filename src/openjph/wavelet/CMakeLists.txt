
add_subdirectory(general)

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    add_subdirectory(avx512)
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
    add_subdirectory(neon)
endif()