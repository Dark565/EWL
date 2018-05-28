#pragma once

#include <vector>
#include <QL/Definitions/defs.hpp>
#include <QL/Arrays/array.hpp>

namespace q3d {
    template<int T> struct VertexArray {
    private:
        std::vector<ql::Array<T>> v_a;
    public:
        constexpr ql::Array<T>& getVertex(size_t p);
        constexpr void addVertex(ql::Array<T>& vertex);
        constexpr removeVertex(size_t p);
    };
}

#include "vertex.inl"