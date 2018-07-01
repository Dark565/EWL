#include <QL/System/Console/console.hpp>

#include <stdio.h>

ql::console& ql::console::gotoxy(int x, int y, std::ostream& os) {
    os << (char)0x1B << '[' << y << ';' << x << 'f';
    return def_console;
}

ql::console& ql::console::color(const ql::Pixel& col, std::ostream& os) {
    os << '\x1b' << "[38;2;" << (int)col.r << ';' << (int)col.g << ';' << (int)col.b << 'm';
    return def_console;
}

ql::console& ql::console::reset_color(std::ostream& os) {
    os << "\033[0m";
    return def_console;
}

std::ostream& operator<<(std::ostream& o, const ql::console& c) {
    return o;
}

std::ostream& operator <<(std::ostream& o, const ql::Pixel& col) {
    ql::console::color(col,o);
    return o;
}

ql::console ql::console::def_console;