#pragma once

#include <memory>

#include "sorter.hpp"
#include "std_sorter.hpp"

namespace bitonic_sort::app {

enum class Backend {
    kCpu = 0,
    kOpenCl = 1,
};

template <typename T>
std::unique_ptr<domain::ISorter<T>> MakeSorter(Backend b) {
    switch (b) {
        case Backend::kCpu:
            return std::make_unique<infra::cpu::StdSorter<T>>();
        default:
            throw std::runtime_error("Unknown backend");
    }
}

} // namespace bitonic_sort::app
