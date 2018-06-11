#pragma once

#include "../Renderers/renderers.hpp"

namespace q3d {

    struct Axis  {
        float ang;
        float fov;
    };

    class Camera {
        ql::type::vec3f pos;
        Axis axis_x, axis_y;


    };
}