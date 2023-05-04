#ifndef LIST_H
#define LIST_H

#include "node.h"

template <typename T>
class LinkedList {
    Node<T>* head = nullptr;
    int size = 0;
public:
    LinkedList();
    ~LinkedList();
    LinkedList(Node<T>* head);
    LinkedList(Node<T>* head, Node<T>* tail);
    void push_front(T data);
    void add_node(T data, bool add_to_end);
    void add_node(T data, Node<T>* specific_node);
    void add_node(Node<T> data, Node<T>* specific_node);
    Node<T>* find_node(T key);
    Node<T>* find_mid_node();
    Node<T>* binary_find_node(T key, Node<T>* &lower_node, int high, int lower = 1);
    bool remove_node(T key);
    bool remove_node(Node<T>* node);
    bool swap_node(Node<T>* &x, Node<T>* &y);
    int length() { return size; };
    Node<T>* front() { return head; };
};

#endif