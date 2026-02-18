#pragma once

#include <variant>

#include "parse_cli.hpp"
#include "sorter_factory.hpp"

namespace bitonic_sort::app {

inline SorterConfig ToSorterConfig(ParseResult&& res) {
    if (auto* cpu = std::get_if<CpuConfig>(&res)) {
        return *cpu;
    }
    if (auto* opencl = std::get_if<OpenClConfig>(&res)) {
        return *opencl;
    }
    throw std::logic_error("ToSorterConfig: ExitAction must be handled before calling this");
}

} // namespace bitonic_sort::app
