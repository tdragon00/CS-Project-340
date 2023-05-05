#include "node.h"

template <typename T>
Node<T>::Node(T data)
{
    this->data = data;
}

template <typename T>
Node<T>::~Node()
{
    this->next = nullptr;
    this->prev = nullptr;

    delete this;
}

template <typename T>
T Node<T>::get_data()
{
    return this->data;
}

template <typename T>
Node<T>* Node<T>::get_next() {
    return this->next;
}

template <typename T>
void Node<T>::set_next(Node* newNode) {
    this->next = newNode;
}

template <typename T>
Node<T>* Node<T>::get_prev() {
    return this->prev;
}

template <typename T>
void Node<T>::set_prev(Node* newNode) {
    this->prev = newNode;
}