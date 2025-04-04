#!/bin/bash
#rm -rf build
# TODO: Move these to CMakeUserPresets.json
#export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
#export LDFLAGS="-L/opt/homebrew/opt/llvm/lib"
#export CPPFLAGS="-I/opt/homebrew/opt/llvm/include"
mkdir -p build
#CONFIGPRESET="debug"
CONFIGPRESET="release"

#BUILDPRESET="debug"
#BUILDPRESET="debug-with-tests"
#BUILDPRESET="release"
#BUILDPRESET="release-with-tests"
BUILDPRESET="benchmark"

#TESTPRESET="debug-test-all"
#TESTPRESET="release-test-all"
TESTPRESET="benchmark-test-all"

# use cmake to configure the build
# TODO: Move -DCMAKE* to CMakeUserPresets.json
cmake \
    . \
    --preset $CONFIGPRESET \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ 

if [ $? -ne 0 ]; then
    exit 1
fi

# use cmake to do the build
cmake \
    --build \
    --preset $BUILDPRESET 

if [ $? -ne 0 ]; then
    exit 1
fi

# use ctest to test
if [ -n "$TESTPRESET" ]; then
    echo "Running CTEST"
    ctest -j --build-config $BUILDPRESET --preset $TESTPRESET -R ^OPENJPH -j 
    #ctest --test-dir build --build-config $BUILDPRESET --preset $TESTPRESET -R ^OPENJPH -j 
    if [ $? -ne 0 ]; then
        exit 1
    fi
fi


# run benchmarks if configured
if [ "$CONFIGPRESET" == "release" ] && [ "$BUILDPRESET" == "benchmark" ]; then
    build/release/benchmarks/openjph-benchmark
fi