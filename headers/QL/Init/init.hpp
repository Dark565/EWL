#pragma once

#include "../Error/error.hpp"
#include "../Definitions/defs.hpp"

namespace ql {

    /*Inits the program
    /Doesn't work if program was inited before*/

    bool init(int argc, char** argv, error_ft err_f = NULL);
}