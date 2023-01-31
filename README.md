# GetLabelsFromDataset

An application for counting classes in [Labelme](https://github.com/wkentaro/labelme) markup files.

## Assembly

1. If necessary, activate the Python environment containing the Conan executable.
2. build_v142_x64.cmd for Windows to create and compile a Visual Studio 2019 project. build_ninja.sh for Linux to create and compile project.

### Example

Windows:

> build_v142_x64.cmd Debug

Linux:

> build_ninja.sh Debug

## Requirements

* [CMake](https://cmake.org/download/) >= 3.18
* [Conan](https://conan.io/downloads.html)
  * VS 2019 (Community, Workload NativeDesktop, vcredist140, WinDbg)
  * GCC >=8

_Optional:_

* [Ninja](https://github.com/ninja-build/ninja/releases)
* [vswhere](https://github.com/microsoft/vswhere/releases)

## Dependencies

The project contains the following types of dependencies that can be updated:

* Conan dependencies.
* CMake fetchContent dependencies.

## Composition

The project contains the following modules in the form of a monorepository:

### Projects

* **GetLabels** is the executable file of the project.

### Solution Environment

* **cmake** - CMake modules and helpers.

* **scripts** - build scripts and utilities.

## Usage example

Run the program by passing it the path to the directory with the markup files as the first argument.


> GetLabels ./example/
