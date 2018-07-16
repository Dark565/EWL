#include <QL/System/error.hpp>

#include <iostream>

void ql::error(const char* err) {
    std::cerr << err;
    abort();
}