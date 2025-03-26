#rm -rf build
mkdir -p build
cd build
cmake .. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DBUILD_TESTING=ON
#make -j && ctest
#make -j && tests/openjph/openjph-unittest
make -j && tests/openjph/wavelet/general/openjph-wavelet-general-test