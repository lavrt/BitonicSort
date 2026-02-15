#pragma once

#include <algorithm>
#include <span>

#include "sorter.hpp"
#include "sort_options.hpp"

template <typename T>
class StdSorter final : public ISorter<T> {
public:
    void sort(std::span<T> data, SortOptions opt = {}) override {
        std::sort(data.begin(), data.end());
    }

    std::string name() const override {
        return "std::sort";
    }
};
