# mac os x homebrew current version = 3.31
cmake_minimum_required(VERSION 3.28)

project(OpenJPH LANGUAGES CXX)

# Options
option(BUILD_SHARED_LIBS "Shared Libraries" ON)
option(OJPH_BUILD_TESTING "Build OpenJPH Tests" OFF)
option(OJPH_BUILD_EXECUTABLES "Enables building command line executables" ON)
option(OJPH_BUILD_BENCHMARKS "Enables building benchmark" OFF)


# set the build type if not specified
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}")
endif()


# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    #set(CMAKE_CXX_CLANG_TIDY clang-tidy)

    # configure build settings 
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    # Let's ensure -std=c++xx instead of -std=g++xx
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Let's nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

# enable architecture specific optimizations
add_compile_options(-march=native)

# The compiled library code is here
add_subdirectory(src)

# The executable code is here
if (OJPH_BUILD_EXECUTABLES)
  #add_subdirectory(apps)
endif()

set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/external")

# Testing only available if this is the main app
# Emergency override OPENJPG_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR OJPH_BUILD_TESTING) AND BUILD_TESTING)

    include(CTest)

    enable_testing()

    add_subdirectory(tests)

endif()

if( OJPH_BUILD_BENCHMARKS)

    add_subdirectory(benchmarks)

endif()
