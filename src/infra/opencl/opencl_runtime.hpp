#pragma once 

#include <vector>

#include "opencl_config.hpp"

namespace bitonic_sort::infra::opencl {

enum class DeviceKind {
    kPreferGpu,
    kPreferCpu,
    kCpuOnly,
    kGpuOnly,
};

class OpenClRuntime {
public:
    OpenClRuntime(DeviceKind kind) {
        PickPlatformAndDevice(GetPlatforms(), kind);
        context_ = cl::Context(device_);
        queue_ = cl::CommandQueue(context_, device_);
    }

private:
    cl::Platform platform_;
    cl::Device device_;
    cl::Context context_;
    cl::CommandQueue queue_;

    static std::vector<cl::Platform> GetPlatforms() {
        std::vector<cl::Platform> platforms;
        
        if (cl::Platform::get(&platforms); platforms.empty()) {
            throw std::runtime_error("No OpenCL platforms found");
        }

        return platforms;
    }

    void PickPlatformAndDevice(const std::vector<cl::Platform>& platforms, DeviceKind kind) {
        auto try_pick = [&platforms, this](cl_device_type type) {
            for (const auto& p : platforms) {
                std::vector<cl::Device> devs;
                try {
                    p.getDevices(type, &devs);
                } catch (const cl::Error&) {
                    continue;
                }

                if (!devs.empty()) {
                    platform_ = p;
                    device_ = devs.front();
                    return true;
                }
            }
            return false;
        };

        switch (kind) {
            case DeviceKind::kPreferGpu:
                if (try_pick(CL_DEVICE_TYPE_GPU)) return;
                if (try_pick(CL_DEVICE_TYPE_CPU)) return;
                throw std::runtime_error("No OpenCL GPU/CPU devices found (PreferGpu)");
            case DeviceKind::kPreferCpu:
                if (try_pick(CL_DEVICE_TYPE_CPU)) return;
                if (try_pick(CL_DEVICE_TYPE_GPU)) return;
                throw std::runtime_error("No OpenCL GPU/CPU devices found (PreferCpu)");
            case DeviceKind::kGpuOnly:
                if (try_pick(CL_DEVICE_TYPE_GPU)) return;
                throw std::runtime_error("No OpenCL GPU devices found (GpuOnly)");
            case DeviceKind::kCpuOnly:
                if (try_pick(CL_DEVICE_TYPE_CPU)) return;
                throw std::runtime_error("No OpenCL CPU devices found (CpuOnly)");
        }

        throw std::runtime_error("Unknown DeviceKind");
    }
};

} // bitonic_sort::infra::opencl
