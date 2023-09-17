# How to run your files CORRECTLY

## touch CMakeLists.txt //az adott óra mappájába (itt a tutorial)

## Tartalma legyen:
```c
cmake_minimum_required(VERSION 3.10)
project(MyProject)
find_package(OpenCV REQUIRED)
add_executable(MyProject main.cpp) //main.cpp mindig az adott futtatni kivant file-od
target_link_libraries(MyProject ${OpenCV_LIBS})
```

mkdir build

cd build

cmake ..

make

./MyProject

> ha kell valami kép vagy videó hozzá akkor azt is a build mappába tedd, elérésként a teljes path-t add majd meg