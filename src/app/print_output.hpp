#pragma once 

#include <ostream>
#include <vector>

namespace bitonic_sort::app {

template <typename T>
void PrintVector(std::ostream& out, const std::vector<T>& vec) {
    for (const auto& value : vec) {
        out << value << " ";
    }
    out << "\n";
}

} // namespace bitonic_sort::app
