#pragma once 

#include <ostream>
#include <vector>

namespace bitonic_sort::app {

template <typename T>
void PrintVector(std::ostream& out, const std::vector<T>& vec) {
    for (size_t i = 0; i != vec.size(); ++i) {
        out << vec[i] << (i + 1 == vec.size() ? "\n" : " ");
    }
}

} // namespace bitonic_sort::app
