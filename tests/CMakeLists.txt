include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

# Locate Google Test
#find_package(GTest REQUIRED)

# Include Google Test module
include(GoogleTest)

add_subdirectory(openjph)
