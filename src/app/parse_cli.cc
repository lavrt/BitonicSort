#include "parse_cli.hpp"

#include <filesystem>
#include <sstream>
#include <stdexcept>

#include <boost/program_options.hpp>

namespace {

bitonic_sort::infra::opencl::DeviceKind ParseDeviceKind(const std::string& dev) {
    using K = bitonic_sort::infra::opencl::DeviceKind;
    if (dev == "cpu") return K::kCpuOnly;
    if (dev == "gpu") return K::kGpuOnly;
    if (dev == "prefer-cpu") return K::kPreferCpu;
    if (dev == "prefer-gpu") return K::kPreferGpu;
    throw std::runtime_error("Unknown --device value: " + dev);
}

} // namespace

namespace bitonic_sort::app {

std::pair<CliResult, std::optional<SorterConfig>> ParseCli(int argc, const char** argv) {
    namespace po = boost::program_options;
    
    po::options_description desc("Options");
    desc.add_options()
        (
            "help,h",
            "show this help and exit"
        )
        (
            "desc",
            po::bool_switch(),
            "sort in descending order"
        )
        (
            "backend,b",
            po::value<std::string>()->default_value("opencl"),
            "backend to use: cpu|opencl"
        )
        (
            "device,d",
            po::value<std::string>()->default_value("gpu"),
            "(OpenCL only) OpenCL device selection: cpu|gpu|prefer-cpu|prefer-gpu"
        )
        (
            "kernel,k", po::value<std::string>()->default_value("kernels/bitonic.cl"),
            "(OpenCL only) path to OpenCL kernel source, if path is relative it is resolved"
            "relative to the executable directory <exe_dir> (<exe_dir> is the directory containing"
            "the 'sort' executable)"
        );
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    std::ostringstream help_text;
    help_text
        << "Usage:\n"
        << "  sort [options] < input\n"
        << "\n"
        << desc
        << "\n"
        << "Input:\n"
        << "  N followed by N elements\n"
        << "\n"
        << "Output:\n"
        << "  N elements sorted, separated by spaces\n";

    if (vm.count("help")) {
        return {
            CliResult{
                .mode = CliMode::kExit,
                .exit_action = {
                    .exit_code = 0,
                    .exit_text = help_text.str()
                }
            },
            std::nullopt
        };
    }

    const std::string backend = vm["backend"].as<std::string>();
    const bool descending = vm["desc"].as<bool>();

    if (backend == "cpu") {
        return {
            CliResult{},
            CpuConfig{
                .opt{.ascending = !descending}
            }
        };
    }
    
    if (backend == "opencl") {
        return {
            CliResult{},
            OpenClConfig{
                .opt{.ascending = !descending},
                .kind = ParseDeviceKind(vm["device"].as<std::string>()),
                .kernel_path = vm["kernel"].as<std::string>()
            }
        };
    }

    throw std::runtime_error("Unknown --backend value: " + backend);
}

} // namespace bitonic_sort::app
