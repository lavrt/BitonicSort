#pragma once 

#include <ostream>
#include <ranges>
#include <vector>

namespace bitonic_sort::app {

template <typename T>
void PrintVector(std::ostream& out, const std::vector<T>& vec) {
    if (vec.empty()) {
        return;
    }
    std::ranges::copy(vec.begin(), std::prev(vec.end()), std::ostream_iterator<T>(out, " "));
    out << vec.back() << "\n";
}

} // namespace bitonic_sort::app
