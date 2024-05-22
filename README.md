<br>

<h1 align="center">Template for C++ Project Setup</h1>
<p align="center">
  <a href="https://img.shields.io/badge/C%2B%2B-20-blue"><img src="https://img.shields.io/badge/C%2B%2B-20-blue" alt="C++"></a>
  <a href="https://img.shields.io/badge/CMake-3.27.6-blue"><img src="https://img.shields.io/badge/CMake-3.27.6-blue" alt="CMake"></a>
  <a href="https://img.shields.io/badge/clang-14.0.3-blue"><img src="https://img.shields.io/badge/clang-14.0.3-blue" alt="clang"></a>
  <a href="https://img.shields.io/badge/Test-GoogleTest-blue"><img src="https://img.shields.io/badge/Test-GoogleTest-blue" alt="Google Test"></a><br>
  Ready-to-use setup for a new C++ project.
</p>

<br>

<br>

The final setup will have the following structure:
```
└─cpp/
    ├─ CMakeLists.txt
    ├─ main.cpp
    ├─ src/
    |    └─ CMakeLists.txt
    └─ test/
         ├─ CMakeLists.txt
         └─ googletest/
```

Files can then be added in the `src` folder, with the corresponding tests added in `test` folder.<br>
Once the files are added, nothing needs to be modified in the `CMakeLists.txt` files (only an updated build is needed).

Pre-requisites:
- A compiler for C++ is already installed, this repo uses `clang` 14.0.3
- CMake is already installed, this repo uses version 3.27.6

# Setup (downloading this repo)

1. Start with a clean directory, say `../cpp`.

2. Download this repository:
```terminal
curl -L https://github.com/paulinamoskwa/cpp_project_template/archive/refs/heads/main.zip -o main.zip
unzip main.zip -d tmp && rsync -av tmp/cpp_project_template-main/ . && rm -rf tmp && rm main.zip
```

3. Enter the `test` folder from terminal and clone `googletest`:
```terminal
git clone https://github.com/google/googletest.git
```

**The setup is now done.** ✨

## Test the setup 

- To build, run from terminal (`cd` to main folder):
```terminal
rm -rf build/ 
mkdir build && cd build
cmake ..
make 
```

- Run tests:
```terminal
test/MyProjectTests
```
which outputs:
```terminal
➜  build test/MyProjectTests
Running main() from /../cpp/template/test/googletest/googletest/src/gtest_main.cc
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from MyMathTest
[ RUN      ] MyMathTest.Add
[       OK ] MyMathTest.Add (0 ms)
[----------] 1 test from MyMathTest (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
```

- Run main:
```terminal
./MyProjectMain
```
which outputs:
```terminal
➜  build ./MyProjectMain
Add: 8
```

<br>

------

<br>

# Setup - alternative version (from scratch)

1. Start with a clean directory, say `../cpp`.

2. Create two empty folders, `src` and `test`, following the structure:
```
└─cpp/
    ├─ src/
    └─ test/
```

3. Enter the `test` folder from terminal and clone `googletest`:
```terminal
git clone https://github.com/google/googletest.git
```

The structure at this point has to be:
```
└─cpp/
    ├─ src/
    └─ test/
         └─ googletest/
```

4. Create three `CMakeLists.txt`, as follow:
```
└─cpp/
    ├─ CMakeLists.txt
    ├─ src/
    |    └─ CMakeLists.txt
    └─ test/
         ├─ CMakeLists.txt
         └─ googletest/
```
with the following content:
- root `CMakeLists.txt`
```cmake
# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(MyProject VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(test)

# Add directories for includes
include_directories(src)

# Add the main executable
add_executable(MyProjectMain main.cpp)

# Link the main executable with the project library
target_link_libraries(MyProjectMain PRIVATE MyProjectLib)
```

- `src/CMakeLists.txt`
```cmake
# Get all the source files
file(GLOB_RECURSE SOURCES "*.cpp")

# Add library target (if there are libraries in src)
add_library(MyProjectLib ${SOURCES})
```

- `test/CMakeLists.txt`
```cmake
# Enable testing
enable_testing()

# Add subdirectory
add_subdirectory(googletest)

# Add include directories for GoogleTest
include_directories(googletest/include)

# Get all the test source files from the test directory and its subdirectories
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Add the test executable
add_executable(MyProjectTests ${TEST_SOURCES})

# Link the test executable with the GoogleTest libraries and the project library
target_link_libraries(MyProjectTests PRIVATE GTest::gtest GTest::gtest_main MyProjectLib)
target_include_directories(MyProjectTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src)

# Discover and add tests
include(GoogleTest)
gtest_discover_tests(MyProjectTests)
```

5. Finally, create an empty `main.cpp` inside the `src` folder.
```
└─cpp/
    ├─ CMakeLists.txt
    ├─ main.cpp
    ├─ src/
    |    └─ CMakeLists.txt
    └─ test/
         ├─ CMakeLists.txt
         └─ googletest/
```

**The setup is now done.** ✨

## Test the setup

- Create two files inside `src`: `SimpleFile.h`, `SimpleFile.cpp`.
```cpp
// SimpleFile.h

#ifndef SIMPLEFILE_H
#define SIMPLEFILE_H

int add(int a, int b);

#endif // SIMPLEFILE_H
```

```cpp
// SimpleFile.cpp

#include "SimpleFile.h"

int add(int a, int b) {
    return a + b;
}
```

- Create the test for this new file; create `TestSimpleFile.cpp` in the `test` folder.
```cpp
#include <gtest/gtest.h>
#include "SimpleFile.h"

TEST(MyMathTest, Add) {
    ASSERT_EQ(add(1, 1), 2);
    ASSERT_EQ(add(-1, 1), 0);
    ASSERT_EQ(add(-1, -1), -2);
}
```

- Update `main.cpp`.
```cpp
#include <iostream>
#include "SimpleFile.h"

int main() {
    int a = 5, b = 3;
    std::cout << "Add: " << add(a, b) << std::endl;
    return 0;
}
```

- Build; run from terminal (`cd` to main folder):
```terminal
rm -rf build/ 
mkdir build && cd build
cmake ..
make 
```

- Run tests:
```terminal
test/MyProjectTests
```
which outputs:
```terminal
➜  build test/MyProjectTests
Running main() from /../cpp/template/test/googletest/googletest/src/gtest_main.cc
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from MyMathTest
[ RUN      ] MyMathTest.Add
[       OK ] MyMathTest.Add (0 ms)
[----------] 1 test from MyMathTest (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
```

- Run main:
```terminal
./MyProjectMain
```
which outputs:
```terminal
➜  build ./MyProjectMain
Add: 8
```
