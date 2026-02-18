#pragma once

#include <filesystem>
#include <stdexcept>
#include <string>
#include <variant>

#include <boost/program_options.hpp>

#include "opencl_runtime.hpp"

namespace bitonic_sort::app {

namespace po = boost::program_options;

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

inline infra::opencl::DeviceKind ParseDeviceKind(const std::string& dev) {
    using K = infra::opencl::DeviceKind;
    if (dev == "cpu") return K::kCpuOnly;
    if (dev == "gpu") return K::kGpuOnly;
    if (dev == "prefer-cpu") return K::kPreferCpu;
    if (dev == "prefer-gpu") return K::kPreferGpu;
    throw std::runtime_error("Unknown --device value: " + dev);
}

inline ParseResult ParseCli(int argc, char** argv) {
    po::options_description desc("Options");
    desc.add_options()
        ("help,h", "Show help")
        ("backend", po::value<std::string>()->default_value("opencl"), "cpu|opencl")
        ("device", po::value<std::string>()->default_value("gpu"), "cpu|gpu|prefer-cpu|prefer-gpu")
        ("kernel", po::value<std::string>()->default_value("kernels/bitonic.cl"), "Path to kernel.cl");
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        return ExitAction{0, "Usage: sort [options]\n"}; // TODO
    }

    const std::string backend = vm["backend"].as<std::string>();

    if (backend == "cpu") {
        return CpuConfig{};
    }
    
    if (backend == "opencl") {
        return OpenClConfig{
            .kind = ParseDeviceKind(vm["device"].as<std::string>()),
            .kernel_path = vm["kernel"].as<std::string>()
        };
    }

    throw std::runtime_error("Unknown --backend value: " + backend);
}

} // namespace bitonic_sort::app
