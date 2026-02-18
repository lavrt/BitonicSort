#pragma once

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

namespace bitonic_sort::app {

inline std::string LoadKernelFile(const std::filesystem::path& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Failed to load kernel file: " + path.string());
    }

    return std::string{
        std::istreambuf_iterator<char>(in),
        std::istreambuf_iterator<char>()
    };
}

inline std::filesystem::path GetExeDir() {
    return std::filesystem::read_symlink("/proc/self/exe").parent_path();
}

} // namespace bitonic_sort::app
