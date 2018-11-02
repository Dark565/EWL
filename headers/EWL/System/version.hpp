#pragma once

#define QL_VERSION "Dev 0.3"
#define QL_NAME "EWL"
#define QL_RELEASE "EWL 0.3 07.2018"

namespace ewl {

    /* Gets version of the dynamic library */

    const char* getVersion();

    /* Gets name of the dynamic library*/

    const char* getName();

    /* Gets release version of the dynamic library*/

    const char* getRelease();
}