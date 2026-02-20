#pragma once

#include <optional>
#include <string>

#include "sorter_configs.hpp"

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

std::pair<CliResult, std::optional<SorterConfig>> ParseCli(int argc, const char** argv);

} // namespace bitonic_sort::app
