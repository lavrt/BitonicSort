#include <iostream>
#include <memory>
#include <span>
#include <stdexcept>
#include <string>
#include <vector>

#include "parse_cli.hpp"
#include "parse_input.hpp"
#include "print_output.hpp"
#include "sorter_factory.hpp"
#include "sort_options.hpp"

using Elem = int;

namespace App = bitonic_sort::app;

int main(int argc, char** argv) {
    try {
        auto [program, cfg] = App::ParseCli(argc, argv);
        if (program.mode == App::CliMode::kExit) {
            std::cout << program.exit_action.exit_text;
            return program.exit_action.exit_code;
        }

        auto sorter = App::MakeSorter<Elem>(cfg.value());
        std::vector<Elem> data = App::ReadInput<Elem>(std::cin);

        const auto& opt = std::visit([](const auto& c) {
            return c.opt;
        }, cfg.value());
        sorter->Sort(data, opt);
        
        App::PrintVector(std::cout, data);
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
