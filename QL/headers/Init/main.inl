#pragma once

#include "init.hpp"

int main(int argc, char** argv) {
    ql::init(argc, argv, ql::_ERR_D);
    return ql::main(argc, argv);
}