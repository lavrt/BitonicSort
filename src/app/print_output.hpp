#pragma once 

#include <ostream>
#include <vector>

template <typename T>
inline void PrintVector(std::ostream& out, const std::vector<T>& vec) {
    for (const auto& value : vec) {
        out << value << " ";
    }
    out << "\n";
}
