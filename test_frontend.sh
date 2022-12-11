cd DoIt/frontend;

cmake -B ./build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON;

cmake --build build;

cd build && ctest;

