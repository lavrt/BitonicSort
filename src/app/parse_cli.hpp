#pragma once

#include <filesystem>
#include <string>

#include "sorting_configs.hpp"
#include "device_kind.hpp"

namespace bitonic_sort::app {

infra::opencl::DeviceKind ParseDeviceKind(const std::string& dev);
ParseResult ParseCli(int argc, char** argv);

} // namespace bitonic_sort::app
