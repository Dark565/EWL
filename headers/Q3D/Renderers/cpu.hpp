#pragma once

#include "renderers.hpp"
#include "../Render/camera.hpp"
#include "CPU/renderables.hpp"
#include "CPU/chunk.hpp"
#include "CPU/space.hpp"
#include <vector>

namespace q3d {
    class CPU : public Renderer {
        cpu::Chunk ch;
    public:
        cpu::Space* wrl;
        
        virtual bool renderSolid(VertexArray<3>& arr, ql::type::vec3f pos, ql::Pixel col);
        bool generateChunk();
    };
}