#ifndef LIST_NODE_H
#define LIST_NODE_H

template<typename T>
struct ListNode {
    uint16_t m_next;
    uint16_t m_prev;
    T        m_value;
};

#endif // LIST_NODE_H