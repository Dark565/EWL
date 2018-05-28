#pragma once

#include "renderables.hpp"

namespace q3d {
    namespace cpu {
        namespace shapes {

            class Shape : public Renderable  {

                private: Shape() = delete;
            };

            class Polygon : public Shape {
            public:
                VertexArray<2> ver_arr;

                virtual bool intersect(ql::type::vec3f ray);
            };

            class Circle : public Shape {
            public:
                float radius;

                virtual bool intersect(ql::type::vec3f ray);
            };
        }
    }
}