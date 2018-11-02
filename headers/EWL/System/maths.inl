template <class T>
constexpr bool ewl::maths::isBit(T v, uint8_t b) {
    return (v & (1 << b));
}

template <class T>
constexpr ewl::size_t ewl::maths::countBits(T v) {
    ewl::size_t bits = 0;
    for(ewl::uint32_t i = 0; i < sizeof(T) * 8; i++) if(ewl::maths::isBit(v,i)) bits++;
    return bits;
}