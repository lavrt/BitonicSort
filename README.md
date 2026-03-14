# BitonicSort

**BitonicSort** is a C++20 application for sorting integer sequences using either a CPU backend based on `std::sort` or an OpenCL-based bitonic sort implementation.

## Overview

BitonicSort is a small modular C++ application with a layered architecture and clear separation of concerns:
- a **domain layer** that defines a common sorter interface
- an **application layer** that handles CLI parsing, input loading, backend selection, and output formatting
- an **infrastructure layer** that provides two interchangeable implementations:
  - a **CPU backend** based on `std::sort`
  - an **OpenCL backend** based on a bitonic sorting kernel

## Features

- modern C++20 codebase
- modular layered architecture
- interchangeable CPU and OpenCL sorting backends
- CPU sorting based on `std::sort`
- OpenCL sorting based on  bitonic sort
- command-line interface for backend and device selection
- Conan-based dependency management
- CMake-based build

## Project Structure

```text
.
├── CMakeLists.txt
├── conanfile.txt
├── README.md
├── bitonic.cl
└── src/
    ├── main.cc
    ├── app/
    │   ├── file_loader.hpp
    │   ├── parse_cli.cc
    │   ├── parse_cli.hpp
    │   ├── parse_input.hpp
    │   ├── print_output.hpp
    │   ├── sorter_configs.hpp
    │   └── sorter_factory.hpp
    ├── domain/
    │   ├── sorter.hpp
    │   └── sort_options.hpp
    └── infra/
        ├── cpu/
        │   └── std_sorter.hpp
        └── opencl/
            ├── kernels/
            |   └── bitonic.cl
            ├── bitonic_sorter.hpp
            ├── opencl_runtime.hpp
            ├── opencl_config.hpp
            └── device_kind.hpp
```

## Build

The project uses Conan for dependency management and CMake presets for configuration.

```bash
git clone https://github.com/lavrt/BitonicSort
cd BitonicSort

conan install . -of build -s build_type=Release --build=missing
cmake --preset conan-release
cmake --build --preset conan-release -j
```

## Usage

The program reads the number of elements followed by the sequence itself from standard input.

#### Example input

```text
5
9 -1 7 3 2
```

#### Example run with the CPU backend

```bash
echo "5 9 -1 7 3 2" | ./build/sort --backend cpu
```

#### Example run with the OpenCL backend and explicit device selection

```bash
echo "5 9 -1 7 3 2" | ./build/sort --backend opencl --device prefer-gpu
```

#### Example output
For the input `5 9 -1 7 3 2` the program prints:
```bash
-1 2 3 7 9
```

## CLI Options

Supported options:
- `--help`, `-h` — print usage information
- `--desc` — sort in descending order
- `--backend cpu|opencl` — select the sorting backend
- `--device cpu|gpu|prefer-cpu|prefer-gpu` — select the OpenCL device
- `--kernel <path>` — specify the path to the OpenCL kernel source

## Current Limitations

The current OpenCL backend is a straightforward baseline implementation of bitonic sort, chosen for clarity and correctness. Future iterations of the project will focus on performance improvements and more optimized kernel design.
