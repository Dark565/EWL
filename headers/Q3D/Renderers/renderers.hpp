#pragma once

#include <QL/Definitions/types.hpp>
#include <QL/Colorize/colors.hpp>
#include "../Vertex/vertex.hpp"


namespace q3d {
    class Renderer {
    public:
        virtual bool renderSolid(VertexArray& arr, ql::type::vec3f p, ql::Pixel col) {}

    private:
        Renderer() = delete;
    };
}