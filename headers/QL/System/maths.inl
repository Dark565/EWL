template <class T>
constexpr bool ql::maths::isBit(T v, uint8_t b) {
    return (v & (1 << b));
}