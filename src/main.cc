#include <iostream>
#include <memory>
#include <vector>

#include "parse_input.hpp"
#include "print_output.hpp"
#include "sorter_factory.hpp"

using Elem = int;

int main() {
    try {
        std::vector<Elem> data = bitonic_sort::app::ReadInput<Elem>(std::cin);

        auto sorter = bitonic_sort::app::MakeSorter<Elem>(bitonic_sort::app::Backend::kCpu);
        sorter->Sort(data);

        bitonic_sort::app::PrintVector(std::cout, data);
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
