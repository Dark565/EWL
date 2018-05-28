#pragma once

#include "renderers.hpp"
#include "CPU/renderables.hpp"
#include "CPU/chunk.hpp"
#include <vector>

namespace q3d {
    class CPU : public Renderer {
        cpu::Chunk ch;
    public:
        virtual bool renderSolid(VertexArray& arr, ql::type::vec3f pos, ql::Pixel col);
        bool generateChunk(std::vector< cpu::Renderable* > rends);
    };
}