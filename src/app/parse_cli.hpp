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
        ("backend,b", po::value<std::string>()->default_value("opencl"), "cpu|opencl")
        ("device,d", po::value<std::string>()->default_value("gpu"), "cpu|gpu|prefer-cpu|prefer-gpu")
        ("kernel,k", po::value<std::string>()->default_value("kernels/bitonic.cl"), "Path to kernel.cl");
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        return ExitAction{
            .code = 0, .text =
            "Usage:\n"
            "  sort [--backend cpu|opencl] [--device gpu|cpu|prefer-gpu|prefer-cpu] [--kernel PATH]\n"
            "  sort --help\n\n"
            "Options:\n"
            "  -h, --help \t\t show this help and exit\n"
            "  -b, --backend=ARG \t backend to use: cpu|opencl,\n"
            "                    \t default is opencl\n"
            "  -d, --device=ARG \t OpenCL device selection:\n"
            "                   \t cpu|gpu|prefer-gpu|prefer-cpu,\n"
            "                   \t default is gpu\n"
            "  -k, --kernel=PATH \t path to OpenCL kernel source,\n"
            "                    \t default is kernels/bitonic.cl\n"
            "                    \t (provided next to the executable),\n"
            "                    \t if PATH is relative it is resolved\n"
            "                    \t relative to the executable directory\n"
            "                    \t (<exe_dir>)\n"
        };
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
