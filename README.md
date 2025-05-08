Remove-Item -Recurse -Force build

cmake -G "Visual Studio 17 2022" -DCMAKE_PREFIX_PATH="C:/Program Files/Slint-cpp 1.11.0" -B build
cmake --build build --config Release
