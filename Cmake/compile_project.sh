cd `dirname $0`
rm -rf build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j
cd ../../
./Cmake/build/bomberman
##LD_LIBRARY_PATH=/usr/local/lib64 ./bomberman
