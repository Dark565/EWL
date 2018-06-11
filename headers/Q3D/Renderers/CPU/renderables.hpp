#pragma once

#include "../renderers.hpp"

namespace q3d {
    namespace cpu {
        
        class Renderable {
        public:
            virtual bool intersect(ql::type::vec3f ray) {return false;}
        };

    }
}