#ifndef LIST_NODE_H
#define LIST_NODE_H

template<typename T>
struct ListNode {
    enum { 
        kNullIdx = 0xffff
    };

    ListNode( uint16_t next, uint16_t prev, T const &value ) :
        m_next( next ), m_prev( prev ), m_value( value ) {}

    uint16_t m_next;
    uint16_t m_prev;
    T        m_value;
};

#endif // LIST_NODE_H