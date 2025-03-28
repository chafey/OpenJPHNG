#rm -rf build
mkdir -p build
cd build
cmake .. \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -DOJPH_BUILD_BENCHMARKS=ON \
    -DBUILD_TESTING=ON \
    -DCMAKE_BUILD_TYPE=Release 
#    -DCMAKE_C_COMPILER=clang \
#    -DCMAKE_CXX_COMPILER=clang++ \
#make -j && ctest
#make -j && tests/openjph/openjph-unittest
make -j && tests/openjph/wavelet/general/openjph-wavelet-general-test && benchmarks/openjph-benchmark