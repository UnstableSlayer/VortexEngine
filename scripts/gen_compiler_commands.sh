cd build
cmake -H. -BDebug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=YES ..
ln -s compile_commands.json ..
