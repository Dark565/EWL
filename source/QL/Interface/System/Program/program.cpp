#include "../Private/Data/data.hpp"
#include <QL/System/Program/program.hpp>

static ql::mystery::data dt;

ql::mystery::data* ql::mystery::getMysteryDataPtr() {
    return &dt;
}

int ql::getArgc() {
    return dt.argc;
}

char** ql::getArgv() {
    return dt.argv;
}