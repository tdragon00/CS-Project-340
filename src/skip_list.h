#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include "list.h"
#include "node.h"

template <typename T>
class SkipList
{
    int size = 0;
    SkipNode<T>* head = nullptr;
    SkipNode<T>* priv_head = nullptr;
    int flip_coin();
public:
    SkipList();
    void insert(T data);
    void remove(T data);
    void pretty_print();

    int length() const { return size; };
    SkipNode<T>* front() const { return head; };
    SkipNode<T>* search(T data, SkipNode<T>* head=nullptr, bool is_begin=true) const;
    bool remove_node(T data);
    bool remove_node(SkipNode<T>* node);
};

#endif