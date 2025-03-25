# OpenJPHNG
Experimental repository for an OpenJPH refactoring.  

# Goals

* Improve readability of code 
    * Minimize abbreviations in class, function and argument names
    * Break large files into several smaller files
    * Break large functions into several smaller functions
* Improve use of C++ language features.  
    * Get rid of function pointers
        * Use polymorphic classes or templates
    * Use const and references
    * Increase minimum c++ version to 17 from 14
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

* Alpha (Mar 25, 2025)

# Building

## Supported build environments:

Current:
| OS           | CPU     | Compiler
| ------------ | ------- | --------
| Mac OS X     | AArch64 | Apple Clang

Future:
| OS           | CPU     | Compiler
| ------------ | ------- | --------
| Linux Ubuntu | x86_64  | gcc
| Windows      | x86_64  | MSVC

## Requirements

* CMake 3.31 or newer
* C++ Build Environment (compiler, linker, make)

## Building

> ./build.sh

# Contributing

* TODO: style guide
* TODO: policies (zero warning, CI passes, unit test coverage?) 
* TODO: Supported IDEs (VS Code, Xcode?, Visual Studio?)

# FAQ

* Q: What version of C++ will this library use?
  - A: TBD - it is currently set to 17 (up from 14 in current OpenJPH).  Feedback on this would be appreciated!
* Q: Will this library be backwards compatible with the current OpenJPH API?
  - A: The APIs will change to improve readability, use modern C++ features and be unit testable so will change.  An adapter layer will be explored in the future 
* Q: Will speed be improved?
  - A: Improved speed is not a goal of this refactor but it is important to avoid any loss in performance
* Q: What new features will this library have?
  - A: Clean integration with third party libraries (e.g. OpenJPEG), runtime switching between algorithms (e.g. SIMD vs general).  New library features are not planned but could happen along the way

# TODO
