#pragma once

#include "../Definitions/defs.hpp"


/*Predefined main for QL initialize*/
int main(int argc, char** argv);

#ifdef __QL_LIBRARY_MAIN_REQUIRED

namespace ql {
    /*Valid main for initialize your programs*/

    int main(int argc, char** argv);
}

#include "main.inl"

#endif