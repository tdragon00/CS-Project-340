#ifndef NODE_H
#define NODE_H

template<typename T>
class Node
{
private:
    T* data;
    Node* next = nullptr;
    Node* prev = nullptr;
public:
    Node(T &data);
    ~Node();
    T get_data() const;

    Node<T>* get_next() const;
    void set_next(Node* newNode);
    Node<T>* get_prev() const;
    void set_prev(Node* newNode);
};
#endif