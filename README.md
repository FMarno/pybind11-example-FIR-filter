# dsp-fir

This is repo is designed to be an example of how to use pybind11 with python, allowing the user to call c++.

This particular code was part of a university assignment of mine so I have removed the python equivalent (the main part of the assignment), but the performance comparison had this result on my laptop with an 8th gen i7:
```
performance comparison with 500 taps, run 1000 times.
all python: 6.6210065
pass to cpp one at a time: 0.09564449999999969
pass full array to cpp: 0.0560243999999992
```

## Submodules
first acquire pybind
```
git submodule init
git submodule update
```

## Windows
### Windows Requirements
* CMake - https://cmake.org/download/
* Ninja (might not be necessary but make wasn't working for me) - https://github.com/ninja-build/ninja/releases
* python3
* CPP compiler
	- visual studio build tools - https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2019
	- clang (requires visual studio toolchain) - https://releases.llvm.org/download.html LLVM 11.0.0 Prebuilt Binaries Windows
You may need to add all these programs to the PATH environment variable

### Windows MSVC Build instructions
```
cmake -S. -B_build
cmake --build _build --config --Release
```
If the first line fails and it's complaining about the compiler try this instead:

### Windows Clang++ Build instructions
```
cmake -S . -B_build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang  -DCMAKE_CXX_COMPILER=clang++
```

CMAKE_C_COMPILER and CMAKE_CXX_COMPILER are used to specify the location of the C and C++ compiler respectively.

## Linux
### Linux Requirements
* cmake
* a cpp compiler
* python3-dev

### Linux Build instructions
```
cmake -S. -B_build -DCMAKE_BUILD_TYPE=Release
cmake --build _build
```


## all platforms run instructions
You should now have a \_build folder with a file called cpp_fir.someplatform.so or cpp_fir.someplatform.pyd
```
python3 fir_filter.py
```
