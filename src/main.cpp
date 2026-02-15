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

using TElem = int;

int main() {
    try {
        std::vector<TElem> data = bitonic_sort::app::ReadInput<TElem>(std::cin);

        auto sorter = bitonic_sort::app::MakeSorter<TElem>(bitonic_sort::app::Backend::kCpu);
        sorter->sort(data);

        bitonic_sort::app::PrintVector(std::cout, data);
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
