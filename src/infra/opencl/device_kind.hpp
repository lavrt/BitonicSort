#pragma once

namespace bitonic_sort::infra::opencl {

enum class DeviceKind {
    kPreferGpu,
    kPreferCpu,
    kCpuOnly,
    kGpuOnly,
};

} // namespace bitonic_sort::infra::opencl
