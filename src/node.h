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
    Node();
    Node(T data);
    ~Node();
    T get_data() const;
    void set_data(T data);

    Node<T>* get_next() const;
    void set_next(Node* newNode);
    Node<T>* get_prev() const;
    void set_prev(Node* newNode);
};

template<typename T>
class SkipNode : public Node<T>
{
    SkipNode<T>* down = nullptr;
    SkipNode<T>* up = nullptr;
    SkipNode<T>* next = nullptr;
    SkipNode<T>* prev = nullptr;
public:
    SkipNode() : Node<T>() {};
    SkipNode(T data) : Node<T>(data) {};

    SkipNode<T>* get_down() const { return down; };
    SkipNode<T>* get_up() const { return up; };
    SkipNode<T>* get_next() const { return this->next; };
    SkipNode<T>* get_prev() const { return this->prev; };
    void set_down(SkipNode<T>* new_node);
    void set_up(SkipNode<T>* new_node);
    void set_prev(SkipNode<T>* new_node);
    void set_next(SkipNode<T>* new_node);
};

#endif