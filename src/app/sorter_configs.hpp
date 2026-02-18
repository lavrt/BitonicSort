#pragma once

#include <filesystem>
#include <string>
#include <variant>

#include "device_kind.hpp"
#include "sort_options.hpp"

namespace bitonic_sort::app {

struct ExitAction {
    int code;
    std::string text;
};

struct CpuConfig {
    domain::SortOptions opt;
};

struct OpenClConfig {
    domain::SortOptions opt;
    infra::opencl::DeviceKind kind;
    std::filesystem::path kernel_path;
};

using ParseResult = std::variant<ExitAction, CpuConfig, OpenClConfig>;
using SorterConfig = std::variant<CpuConfig, OpenClConfig>;

SorterConfig ToSorterConfig(const ParseResult& res);

} // namespace bitonic_sort::app
