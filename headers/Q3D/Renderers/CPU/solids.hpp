#pragma once

#include "renderables.hpp"

namespace q3d {
    namespace cpu {
        namespace solids {

            class Solid : public Renderable {

                private: Solid() = delete;
            };

            class Polyhedron : public Solid {
            public:
                VertexArray<3> ver_arr;

                virtual bool intersect(ql::type::vec3f ray);
            };

            class Sphere : public Solid {
            public:
                float radius;

                virtual bool intersect(ql::type::vec3f ray);
            };
        }
    }
}