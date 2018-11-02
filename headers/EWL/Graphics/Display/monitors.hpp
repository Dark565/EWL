#pragma once

#include <vector>
#include <string>


namespace ewl {


    struct Monitor {

        std::string name;
        int x,y;
        int width_mm, height_mm;
        int width, height;

    };

}