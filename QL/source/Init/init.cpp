#include <Init/init.hpp>
#include "../Private/Data/data.hpp"



bool ql::init(int argc, char** argv) {
    ql::mystery::data* dt = ql::mystery::getMysteryDataPtr();

    dt->argc = argc;
    dt->argv = argv;
    dt->used_WM = 0;
    
    return 1;
}