#include "node.h"

//constructor
template <typename T>
Node<T>::Node(T data)
{
    this->data = new T(data);
}

//destructor
template <typename T>
Node<T>::~Node()
{
    this->next = nullptr;
    this->prev = nullptr;
    delete data;
}
//returns the data
template <typename T>
T Node<T>::get_data() const
{
    return *this->data;
}
//sets the data 
template <typename T>
void Node<T>::set_data(T data)
{
    delete this->data;
    this->data = new T(data);
}
//gets the next data
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


template <typename T>
void SkipNode<T>::set_down(SkipNode<T>* new_node)
{
    this->down = new_node;
}

template <typename T>
void SkipNode<T>::set_up(SkipNode<T>* new_node)
{
    this->up = new_node;
}

template <typename T>
void SkipNode<T>::set_next(SkipNode<T>* new_node)
{
    this->next = new_node;
}

template <typename T>
void SkipNode<T>::set_prev(SkipNode<T>* new_node)
{
    this->prev = new_node;
}