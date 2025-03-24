include(FetchContent)
FetchContent_Declare(
  googletest
  #DOWNLOAD_EXTRACT_TIMESTAMP
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/6910c9d9165801d8827d628cb72eb7ea9dd538c5.zip
)
FetchContent_MakeAvailable(googletest)

# Locate Google Test
#find_package(GTest REQUIRED)

# Include Google Test module

add_subdirectory(openjph)

