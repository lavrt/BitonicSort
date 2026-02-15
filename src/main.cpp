#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120

#include <CL/opencl.hpp>

#include <iostream>
#include <memory>
#include <vector>

#include "parse_input.hpp"
#include "print_output.hpp"
#include "sorter_factory.hpp"

using elem_t = int;

int main() {
    try {
        std::vector<elem_t> data = ReadInput<elem_t>(std::cin);

        auto sorter = MakeSorter<elem_t>(Backend::CPU);
        sorter->sort(data);

        PrintVector(std::cout, data);
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
