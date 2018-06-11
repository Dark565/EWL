#pragma once
#include <string>

namespace ql {
    typedef void(*error_ft)(std::string);
    void error(const char*);
}