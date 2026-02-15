#pragma once

#include <span>

#include "sort_options.hpp"

namespace bitonic_sort::domain {

template <typename T>
class ISorter {
public:
    virtual ~ISorter() = default;
    virtual void sort(std::span<T> data, SortOptions opt = {}) = 0;
    virtual std::string name() const = 0;
};

} // namespace bitonic_sort::domain
