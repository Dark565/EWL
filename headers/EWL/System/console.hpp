#pragma once

#include <EWL/Graphics/colors.hpp>

#include <EWL/Definitions/int.hpp>
#include <iostream>

namespace ewl {
    struct console {

        static console& gotoxy(int x, int y, std::ostream& os = std::cout);
        static console& color(const Pixel& col, std::ostream& os = std::cout);
        static console& reset_color(std::ostream& os = std::cout);

        static console def_console;

    private:
        console() = default;

    };
}

std::ostream& operator << (std::ostream& o, const ewl::console& c);
std::ostream& operator << (std::ostream& o, const ewl::Pixel& col);