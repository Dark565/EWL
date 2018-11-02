#include <EWL/System/console.hpp>

#include <stdio.h>

ewl::console& ewl::console::gotoxy(int x, int y, std::ostream& os) {
    os << (char)0x1B << '[' << y << ';' << x << 'f';
    return def_console;
}

ewl::console& ewl::console::color(const ewl::Pixel& col, std::ostream& os) {
    os << '\x1b' << "[38;2;" << (int)col.r << ';' << (int)col.g << ';' << (int)col.b << 'm';
    return def_console;
}

ewl::console& ewl::console::reset_color(std::ostream& os) {
    os << "\033[0m";
    return def_console;
}

std::ostream& operator<<(std::ostream& o, const ewl::console& c) {
    return o;
}

std::ostream& operator <<(std::ostream& o, const ewl::Pixel& col) {
    ewl::console::color(col,o);
    return o;
}

ewl::console ewl::console::def_console;