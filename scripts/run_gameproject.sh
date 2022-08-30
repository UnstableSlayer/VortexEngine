cwd=$(pwd)
cd build/GameProject
ln -s ../../GameProject/Shaders .
ln -s ../../GameProject/Textures .
ln -s ../../GameProject/Models .
./GameProject
cd $cwd
