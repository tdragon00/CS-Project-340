#include "node.h"

template <typename T>
Node<T>::Node(T &data)
{
    this->data = new T(data);
}

template <typename T>
Node<T>::~Node()
{
    this->next = nullptr;
    this->prev = nullptr;

    delete data;
}

template <typename T>
T Node<T>::get_data() const
{
    return *this->data;
}

template <typename T>
Node<T>* Node<T>::get_next() const
{
    return this->next;
}

template <typename T>
void Node<T>::set_next(Node* newNode)
{
    this->next = newNode;
}

template <typename T>
Node<T>* Node<T>::get_prev() const
{
    return this->prev;
}

template <typename T>
void Node<T>::set_prev(Node* newNode) 
{
    this->prev = newNode;
}