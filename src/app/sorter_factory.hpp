#pragma once

#include <memory>

#include "sorter.hpp"
#include "std_sorter.hpp"

enum class Backend {
    CPU,
    OpenCL
};

template <typename T>
inline std::unique_ptr<ISorter<T>> MakeSorter(Backend b) {
    switch (b) {
        case Backend::CPU: {
            return std::make_unique<StdSorter<T>>();
        }
    }
    throw std::runtime_error("Unknown backend");
}
