#pragma once

#include "../renderers.hpp"
#include "renderables.hpp"
#include <vector>

namespace q3d {
    namespace cpu {

        class Space {
        public:
            std::vector< cpu::Renderable* > obj_vec;
        };

    }
}