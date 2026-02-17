#pragma once

#include <memory>
#include <string>

#include "bitonic_sorter.hpp"
#include "sorter.hpp"
#include "std_sorter.hpp"

namespace bitonic_sort::app {

struct CpuTag {};

struct OpenClTag {
    infra::opencl::DeviceKind kind;
    std::string kernel_src;
};

template <typename T>
std::unique_ptr<domain::ISorter<T>> MakeSorter(const CpuTag&) {
    return std::make_unique<infra::cpu::StdSorter<T>>();
}

template <typename T>
std::unique_ptr<domain::ISorter<T>> MakeSorter(const OpenClTag& cfg) {
    return std::make_unique<infra::opencl::BitonicSorter<T>>(cfg.kernel_src, cfg.kind);
}

} // namespace bitonic_sort::app
