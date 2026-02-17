#pragma once

#include <format>
#include <istream>
#include <stdexcept>
#include <vector>

namespace bitonic_sort::app {

template <typename T>
std::vector<T> ReadInput(std::istream& in) {
    size_t n = 0;
    if (!(in >> n)) {
        throw std::runtime_error("Input error: expected number of elements");
    }

    std::vector<T> data;
    data.reserve(n);

    for (size_t i = 0; i != n; ++i) {
        T value;
        if (!(in >> value)) {
            throw std::runtime_error(std::format("Input error: expected element #{}", i));
        }
        data.push_back(value);
    }

    return data;
}

} // namespace bitonic_sort::app
