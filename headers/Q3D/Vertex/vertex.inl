template <int T>
constexpr q3d::Array<T>& q3d::VertexArray<T>::getVertex(size_t p) {
    return v_a[p];
}

template <int T>
constexpr void q3d::VertexArray<T>::addVertex(ql::Array<T>& vertex) {
    v_a.push_back(vertex);
}

template <int T>
constexpr void q3d::VertexArray<T>::removeVertex(size_t p) {
    v_a.erase(p);
}