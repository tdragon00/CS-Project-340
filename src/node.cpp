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
