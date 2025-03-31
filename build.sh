#rm -rf build
#export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
#export LDFLAGS="-L/opt/homebrew/opt/llvm/lib"
#export CPPFLAGS="-I/opt/homebrew/opt/llvm/include"
mkdir -p build
CONFIGPRESET="debug"
#CONFIGPRESET="benchmark"
BUILDPRESET="debug"
#BUILDPRESET="benchmark"
TESTPRESET="debug-test-all"

# use cmake to configure the build
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
if [[ -v TESTPRESET ]]; then
    ctest --test-dir build --build-config $BUILDPRESET --preset $TESTPRESET -all -R ^OPENJPH -j 
    if [ $? -ne 0 ]; then
        exit 1
    fi
fi


# run benchmarks if configured
if [ "$CONFIGPRESET" == "benchmark" ] && [ "$BUILDPRESET" == "benchmark" ]; then
    build/benchmark/benchmarks/openjph-benchmark
fi