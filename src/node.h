#ifndef NODE_H
#define NODE_H

template<typename T>
class Node
{
    T data;
public:
    Node *next = nullptr;
    Node *prev = nullptr;

    Node(T data);
    ~Node();
    T get_data();
};
#endif
