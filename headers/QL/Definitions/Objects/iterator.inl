template <class T>
constexpr T& ql::iterator<T>::operator *() const {
    return *ptr;
}

template <class T>
constexpr T* ql::iterator<T>::operator ->() const {
    return ptr;
}

constexpr T& ql::iterator<T>::operator ++() {
    return ptr++;
}

template <class T>
constexpr ql::iterator<T>& operator =(ql::iterator<T>& itb) {
    ptr = itb.ptr;
    return *this;
}

template <class T>
constexpr ql::iterator<T>& operator =(T* ptra) {
    ptr = ptra;
    return *this;
}

template <class T>
constexpr bool ql::iterator<T>::operator ==(ql::iterator<T>& itb) const {
    return ptr == itb.ptr;
}

template <class T>
constexpr ql::iterator<T>::iterator(iterator& itb) {
    ptr = itb.ptr;

template <class T>
constexpr ql::iterator<T>::iterator(T* ptra) {
    ptr = ptra;
}