#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <variant>

#include "device_kind.hpp"
#include "sort_options.hpp"

namespace bitonic_sort::app {

enum class CliMode {
    kRun,
    kExit,
};

struct ExitAction {
    int exit_code;
    std::string exit_text;
};

struct CliResult {
    CliMode mode = CliMode::kRun;
    ExitAction exit_action;
};

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
