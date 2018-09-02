template <class T>
constexpr bool ql::maths::isBit(T v, uint8_t b) {
    return (v & (1 << b));
}

template <class T>
constexpr ql::size_t ql::maths::countBits(T v) {
    ql::size_t bits = 0;
    for(ql::uint32_t i = 0; i < sizeof(T) * 8; i++) if(ql::maths::isBit(v,i)) bits++;
    return bits;
}