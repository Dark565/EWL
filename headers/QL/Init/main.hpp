#pragma once

#include "../Definitions/defs.hpp"


/*Predefined main for QL initialize*/
int main(int, char**);

#ifdef __QL_LIBRARY_MAIN_REQUIRED

namespace ql {
    /*Valid main for initialize your programs*/

    int main(int, char**);
}

#include "main.inl"

#endif