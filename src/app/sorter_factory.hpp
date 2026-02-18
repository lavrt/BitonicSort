#pragma once

#include <memory>
#include <string>

#include "bitonic_sorter.hpp"
#include "kernel_loader.hpp"
#include "sorter.hpp"
#include "std_sorter.hpp"

namespace bitonic_sort::app {

using SorterConfig = std::variant<CpuConfig, OpenClConfig>;

template <typename T>
std::unique_ptr<domain::ISorter<T>> MakeSorter(const SorterConfig& cfg) {
    if (auto* mode = std::get_if<CpuConfig>(&cfg)) {
        return std::make_unique<infra::cpu::StdSorter<T>>();
    } else if (auto* mode = std::get_if<OpenClConfig>(&cfg)) {
        return std::make_unique<infra::opencl::BitonicSorter<T>>(
            LoadKernelFile(GetExeDir() / mode->kernel_path),
            mode->kind
        );
    } else {
        throw std::runtime_error("Unknown ParseResult");
    }
}

} // namespace bitonic_sort::app
