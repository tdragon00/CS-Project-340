#ifndef NODE_H
#define NODE_H

template<typename T>
class Node
{
private:
    T data;
    Node* next = nullptr;
    Node* prev = nullptr;
public:
    Node(T data);
    ~Node();
    T get_data();

    Node<T>* get_next();
    void set_next(Node* newNode);
    Node<T>* get_prev();
    void set_prev(Node* newNode);
};
#endif