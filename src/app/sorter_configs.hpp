#pragma once

#include <filesystem>
#include <string>
#include <variant>

#include "device_kind.hpp"
#include "sort_options.hpp"

namespace bitonic_sort::app {

struct CpuConfig {
    domain::SortOptions opt;
};

struct OpenClConfig {
    domain::SortOptions opt;
    infra::opencl::DeviceKind kind;
    std::filesystem::path kernel_path;
};

using SorterConfig = std::variant<CpuConfig, OpenClConfig>;

} // namespace bitonic_sort::app
