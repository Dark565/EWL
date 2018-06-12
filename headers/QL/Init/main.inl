#pragma once

#include "init.hpp"

int main(int argc, char** argv) {
    ql::init(argc, argv);
    return ql::main(argc, argv);
}