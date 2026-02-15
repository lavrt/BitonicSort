#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120

#include <CL/opencl.hpp>

#include <iostream>
#include <vector>
#include <string>

#include "parse_input.hpp"
#include "print_output.hpp"

using elem_t = int;

int main() {
    try {
        std::vector<elem_t> data = ReadInput<elem_t>(std::cin);
        PrintVector(std::cout, data);
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
