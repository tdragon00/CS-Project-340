#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include "list.h"
#include "node.h"

template <typename T>
class SkipList
{
    int size = 0;
    SkipNode<T>* head = nullptr;
    int flip_coin();
    Node<T>* find_insertion(int curr_level, T data, Node<T> curr_node=nullptr);
public:
    SkipList();
    void insert(T data);
    void remove(T data);

    int length() const { return size; };
    SkipNode<T>* front() const { return head; };
};

#endif