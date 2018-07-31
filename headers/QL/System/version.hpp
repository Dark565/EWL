#pragma once

#define QL_VERSION "Dev 0.3"
#define QL_NAME "Qer Library"
#define QL_RELEASE "Qer Library 0.3 07.2018"

namespace ql {

    /* Gets version of the dynamic library */

    const char* getVersion();

    /* Gets name of the dynamic library*/

    const char* getName();

    /* Gets release version of the dynamic library*/

    const char* getRelease();
}