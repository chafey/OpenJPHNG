# OpenJPHNG
Experimental repository for an [OpenJPH](https://github.com/aous72/OpenJPH/) refactoring.  

# Goals

* Improve readability of code 
    * Minimize abbreviations in class, function and argument names
    * Break large files into several smaller files
    * Break large functions into several smaller functions
    * One class per file
    * source files match class names
* Improve use of C++ language features.  
    * Get rid of function pointers
        * Use polymorphic classes or templates
    * Use const and references
    * Increase minimum c++ version to 20 from 14
        * Should allow us to remove types/#defines from the common folder
* Improve cmake design
    * Use modern best practices
    * Simplify build process/configuration
* Improve source code documentation
    * Documentation for classes and methods
* Add unit tests
    * May improve quality if bugs are found
    * Will make it easier/faster to change the code without introducing regression
    * Move test fixtures into another repo referenced via git submodule to keep the size down
* Enable use of code by other projects 
    * (e.g. block encoders/decoders by OpenJPEG)
* Enable runtime selection of optimizations 
    * (e.g. general vs AVX512 vs WASM_SIMD) for flexibility

# Status

* Alpha (Mar 28, 2025)

# Building

## Supported build environments:

Current:
| OS           | CPU       | Compiler
| ------------ | --------- | --------
| Mac OS X     | AArch64   | Apple Clang
| Linux Ubuntu | x86_64    | gcc

Future:
| OS           | CPU       | Compiler
| ------------ | --------- | --------
| Windows      | x86_64    | MSVC
| WASM-SIMD    | WASM-SIMD | EMSCRIPTEN

## Requirements

* CMake 3.28 or newer
* C++ Build Tools (compiler, linker, make)
* Ninja 1.11.1 or newer

### Notes 

* This project depends on [GoolgeTest](https://github.com/google/googletest) for unit testing.  It will automatically be downloaded and compiled if building tests
* This project depends on [Goolge Benchmark](https://github.com/google/benchmark) for benchmarking.  It will automatically be downloaded and compiled if OJPH_BUILD_BENCHMARKS is ON

## Building

> ./build.sh

# Contributing

* TODO: style guide - [google c++ coding standards?](https://google.github.io/styleguide/cppguide.html)
* TODO: policies (zero warning, CI passes, unit test coverage?) 
* TODO: Supported IDEs (VS Code, Xcode?, Visual Studio?)
* Read Agner Fog's [Optimizing Software in C++](https://www.agner.org/optimize/optimizing_cpp.pdf)

# FAQ

* Q: What version of C++ will this library use?
  - A: TBD - it is currently set to 20 (up from 14 in current OpenJPH) to comply with the Google C++ Style Guide.  Feedback on this would be appreciated!
* Q: Will this library be backwards compatible with the current OpenJPH API?
  - A: The APIs will change to improve readability, use modern C++ features and be unit testable.  An adapter layer will be explored in the future 
* Q: Will speed be improved?
  - A: Improved speed is not a goal of this refactor but it is important to avoid any loss in performance
* Q: What new features will this library have?
  - A: Clean integration with third party libraries (e.g. OpenJPEG), runtime switching between algorithms (e.g. SIMD vs general).  New library functionality is not planned but could happen along the way

# TODO

* Make sure it builds on supported platforms
* Setup CI for supported build environments 
* Create a docker image for building
* Iterate on how the reversible wavelet forward transform works until we are happy with it
* Add instructions for using with Visual Studio Code (extensions, configuration?)
* Add instructions for using with XCode?
* Add instructions for using with Visual Studio?
* Add an application (ojph_compress?) skeleton that links to the library
* Add support for different build configurations (debug, release) (via cmake presets?)
