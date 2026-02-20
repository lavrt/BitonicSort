#pragma once

#include <optional>
#include <string>

#include "sorter_configs.hpp"
#include "device_kind.hpp"

namespace bitonic_sort::app {

infra::opencl::DeviceKind ParseDeviceKind(const std::string& dev);
std::pair<CliResult, std::optional<SorterConfig>> ParseCli(int argc, char** argv);

} // namespace bitonic_sort::app
