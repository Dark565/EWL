#pragma once

#include <Colorize/colors.hpp>

#include <cstdint>
#include <iostream>

namespace ql {
    struct console {

        static console& gotoxy(int x, int y, std::ostream& os = std::cout);
        static console& color(const Pixel& col, std::ostream& os = std::cout);
        static console& reset_color(std::ostream& os = std::cout);

        static console def_console;

    private:
        console() = default;

    };
}

std::ostream& operator << (std::ostream& o, const ql::console& c);
std::ostream& operator << (std::ostream& o, const ql::Pixel& col);