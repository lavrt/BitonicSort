#pragma once

#include <filesystem>
#include <string>
#include <variant>

#include "device_kind.hpp"

namespace bitonic_sort::app {

struct ExitAction {
    int code;
    std::string text;
};

struct CpuConfig {};

struct OpenClConfig {
    infra::opencl::DeviceKind kind;
    std::filesystem::path kernel_path;
};

using ParseResult = std::variant<ExitAction, CpuConfig, OpenClConfig>;

infra::opencl::DeviceKind ParseDeviceKind(const std::string& dev);
ParseResult ParseCli(int argc, char** argv);

} // namespace bitonic_sort::app
