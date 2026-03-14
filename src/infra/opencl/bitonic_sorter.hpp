#pragma once 

#include <format>
#include <memory>
#include <stdexcept>
#include <vector>

#include "opencl_runtime.hpp"
#include "sorter.hpp"

namespace bitonic_sort::infra::opencl {

template <typename T>
class BitonicSorter final : public domain::ISorter<T> {
public:
    BitonicSorter(const std::string& src, DeviceKind kind = DeviceKind::kGpuOnly)
        : rt_(std::make_unique<OpenClRuntime>(kind)), program_(cl::Program{rt_->GetContext(), src})
    {
        try {
            program_.build({rt_->GetDevice()});
        } catch (const cl::Error& e) {
            const auto log = program_.getBuildInfo<CL_PROGRAM_BUILD_LOG>(rt_->GetDevice());
            throw std::runtime_error(
                std::format("OpenCL build failed in {} (err={})\n{}", e.what(), e.err(), log)
            );
        }

        step_ = cl::Kernel{program_, "bitonic_step"};
    }

    void Sort(std::span<T> data, domain::SortOptions opt) override {
        const size_t n = data.size();
        if (n <= 1) {
            return;
        }

        const size_t m = std::bit_ceil(n);
        std::vector<T> host(m);
        for (size_t i = 0; i != n; ++i) {
            host[i] = data[i];
        }

        if (m != n) {
            std::fill(host.begin() + n, host.end(), INT_MAX); // FIXME
        }

        cl::Buffer buf(
            rt_->GetContext(),
            CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
            sizeof(int) * host.size(),
            host.data()
        );

        step_.setArg(0, buf);

        for (cl_uint k = 2; k <= static_cast<cl_uint>(m); k <<= 1) {
            for (cl_uint j = k >> 1; j > 0; j >>= 1) {
                step_.setArg(1, j);
                step_.setArg(2, k);
                rt_->GetQueue().enqueueNDRangeKernel(
                    step_,
                    cl::NullRange,
                    cl::NDRange(m),
                    cl::NullRange
                );
            }
        }
        rt_->GetQueue().finish();

        rt_->GetQueue().enqueueReadBuffer(
            buf, CL_TRUE, 0, sizeof(int) * host.size(), host.data()
        );

        for (size_t i = 0; i < n; ++i) data[i] = host[i];

        if (!opt.ascending) {
            std::reverse(data.begin(), data.end()); // FIXME
        }
    }

    std::string Name() const override {
        return "bitonic_sort";
    }

private:
    std::unique_ptr<OpenClRuntime> rt_;
    cl::Program program_;
    cl::Kernel step_;
};

} // namespace bitonic_sort::infra::opencl
