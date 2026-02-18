#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "parse_cli.hpp"
#include "parse_input.hpp"
#include "print_output.hpp"
#include "sorter_factory.hpp"
#include "utils.hpp"

using Elem = int;

namespace App = bitonic_sort::app;

int main(int argc, char** argv) {
    try {
        auto parsed = App::ParseCli(argc, argv);
        if (auto* act = std::get_if<App::ExitAction>(&parsed)) {
            std::cout << act->text;
            return act->code;
        }

        auto sorter = App::MakeSorter<Elem>(App::ToSorterConfig(std::move(parsed)));
        std::vector<Elem> data = App::ReadInput<Elem>(std::cin);
        sorter->Sort(data);
        App::PrintVector(std::cout, data);
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
