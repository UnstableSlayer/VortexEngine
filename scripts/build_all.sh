cwd=$(pwd)
mkdir build
cd build

export CC=clang
export CXX=clang++

cmake ..

make -j8

cd $cwd
