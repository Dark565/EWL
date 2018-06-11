#include <QL/Error/error.hpp>

#include <iostream>

void ql::error(const char* err) {
    std::cerr << err;
    abort();
}