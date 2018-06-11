#pragma once

#include <QL/Definitions/types.hpp>
#include <QL/Colorize/colors.hpp>
#include "../Vertex/vertex.hpp"
#include "../Render/camera.hpp"


namespace q3d {
    class Renderer {
    public:
        Camera* cam;
        virtual bool renderSolid(VertexArray<3>& arr, ql::type::vec3f p, ql::Pixel col) {}

    private:
        Renderer() = delete;
    };
}