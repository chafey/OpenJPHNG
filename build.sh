#rm -rf build
#export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
#export LDFLAGS="-L/opt/homebrew/opt/llvm/lib"
#export CPPFLAGS="-I/opt/homebrew/opt/llvm/include"
mkdir -p build
cd build
cmake .. \
    --preset benchmark \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ 
#make -j && ctest
#make -j && tests/openjph/openjph-unittest
cd ..
cmake  --build . --preset benchmark 
#make -j && tests/openjph/wavelet/general/openjph-wavelet-general-test && benchmarks/openjph-benchmark
#build/benchmark/tests/openjph/wavelet/general/openjph-wavelet-general-test
build/benchmark/tests/openjph/wavelet/neon/openjph-wavelet-neon-test 
build/benchmark/benchmarks/openjph-benchmark