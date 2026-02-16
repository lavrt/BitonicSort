#pragma once

#include <algorithm>
#include <span>

#include "sorter.hpp"
#include "sort_options.hpp"

namespace bitonic_sort::infra::cpu {

template <typename T>
class StdSorter final : public domain::ISorter<T> {
public:
    void Sort(std::span<T> data, domain::SortOptions opt) override {
        if (opt.ascending) {
            std::sort(data.begin(), data.end(), std::less<T>{});
        } else {
            std::sort(data.begin(), data.end(), std::greater<T>{});
        }
    }

    std::string Name() const override {
        return "std::sort";
    }
};

} // namespace bitonic_sort::infra::cpu
