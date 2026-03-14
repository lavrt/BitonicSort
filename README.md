# BitonicSort

**BitonicSort** is a C++20 application for sorting integer sequences using either a standard CPU implementation or an OpenCL-based bitonic sort backend.

## Overview

The project is designed as a small, modular C++ application with a layered architecture and clear separation of concerns:
- a **domain layer** defines a common sorter interface
- an **application layer** handles CLI parsing, input loading, backend selection, and output formatting
- an **infrastructure layer** provides two interchangeable implementations:
  - a **CPU backend** based on `std::sort`
  - an **OpenCL backend** based on a bitonic sorting kernel

## Project Structure

```text
.
├── CMakeLists.txt
├── conanfile.txt
├── README.md
├── bitonic.cl
└── src/
    ├── app/
    │   ├── file_loader.hpp
    │   ├── parse_cli.сс
    │   ├── parse_cli.hpp
    │   ├── parse_input.hpp
    │   ├── print_output.hpp
    │   ├── sorter_configs.hpp
    │   ├── sorter_factory.hpp
    ├── domain/
    │   ├── sorter.hpp
    │   ├── sort_options.hpp
    └── infra/
        ├── cpu/
        │   └── std_sorter.hpp
        └── opencl/
            ├── kernels
                └── bitonic.cl
            ├── bitonic_sorter.hpp
            ├── opencl_runtime.hpp
            ├── opencl_config.hpp
            └── device_kind.hpp
```

## Build

```bash
conan install . -of build -s build_type=Release --build=missing
cmake --preset conan-release
cmake --build --preset conan-release -j
```
