#pragma once

#include <span>

#include "sort_options.hpp"

template <typename T>
class ISorter {
public:
    virtual ~ISorter() = default;
    virtual void sort(std::span<T> data, SortOptions opt = {}) = 0;
    virtual std::string name() const = 0;
};
