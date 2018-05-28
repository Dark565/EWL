#include <QL/Init/init.hpp>
#include <QL/Error/error.hpp>
#include "../Private/Data/data.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>



bool ql::init(int argc, char** argv, error_ft error_f) {
    ql::mystery::data* dt = ql::mystery::getMysteryDataPtr();

    dt->argc = argc;
    dt->argv = argv;
    dt->used_WM = 0;
    

    return 1;
}