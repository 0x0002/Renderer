
// const iterator
template<typename T>
inline ListConstIterator<T>::ListConstIterator() :
    m_list( nullptr ),
    m_idx( 0 ) {
}

template<typename T>
inline ListConstIterator<T>::ListConstIterator( ListIterator<T> const &it ) :
    m_list( it.m_list ),
    m_idx( it.m_idx ) {
}

template<typename T>
inline ListConstIterator<T>::ListConstIterator( ListNode<T> const *list, uint16_t idx ) :
    m_list( list ),
    m_idx( idx ) {
}

template<typename T>
inline ListConstIterator<T>& ListConstIterator<T>::operator++() {
    m_idx = m_list[m_idx].m_next;
    return *this;
}

template<typename T>
inline ListConstIterator<T>& ListConstIterator<T>::operator--() {
    m_idx = m_list[m_idx].m_prev;
    return *this;
}

template<typename T>
inline ListConstIterator<T> ListConstIterator<T>::operator++( int ) {
    ListConstIterator<T> copy = *this;
    m_idx = m_list[m_idx].m_next;
    return copy;
}

template<typename T>
inline ListConstIterator<T> ListConstIterator<T>::operator--( int ) {
    ListConstIterator<T> copy = *this;
    m_idx = m_list[m_idx].m_prev;
    return copy;
}

template<typename T>
inline bool ListConstIterator<T>::operator==( ListConstIterator const &it ) const {
    return m_list == it.m_list && m_idx == it.m_idx;
}

template<typename T>
inline bool ListConstIterator<T>::operator!=( ListConstIterator const &it ) const {
    return !( *this == it );
}

template<typename T>
inline T const& ListConstIterator<T>::operator*() const {
    return m_list[m_idx].m_value;
}

template<typename T>
inline uint16_t ListConstIterator<T>::Idx() const {
    return m_idx;
}

// iterator
template<typename T>
inline ListIterator<T>::ListIterator() :
    m_list( nullptr ),
    m_idx( 0 ) {
}

template<typename T>
inline ListIterator<T>::ListIterator( ListNode<T> *list, uint16_t idx ) :
    m_list( list ),
    m_idx( idx ) {
}

template<typename T>
inline ListIterator<T>& ListIterator<T>::operator++() {
    m_idx = m_list[m_idx].m_next;
    return *this;
}

template<typename T>
inline ListIterator<T>& ListIterator<T>::operator--() {
    m_idx = m_list[m_idx].m_prev;
    return *this;
}

template<typename T>
inline ListIterator<T> ListIterator<T>::operator++( int ) {
    ListIterator<T> copy = *this;
    m_idx = m_list[m_idx].m_next;
    return copy;
}

template<typename T>
inline ListIterator<T> ListIterator<T>::operator--( int ) {
    ListIterator<T> copy = *this;
    m_idx = m_list[m_idx].m_prev;
    return copy;
}

template<typename T>
inline bool ListIterator<T>::operator==( ListIterator const &it ) const {
    return m_list == it.m_list && m_idx == it.m_idx;
}

template<typename T>
inline bool ListIterator<T>::operator!=( ListIterator const &it ) const {
    return !( *this == it );
}

template<typename T>
inline T& ListIterator<T>::operator*() {
    return m_list[m_idx].m_value;
}

template<typename T>
inline uint16_t ListIterator<T>::Idx() const {
    return m_idx;
}