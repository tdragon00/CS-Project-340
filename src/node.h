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
    // TODO: add an up node for later
    SkipNode<T>* down = nullptr;
public:
    SkipNode(T data) : Node<T>(data) {};
    ~SkipNode();

    SkipNode<T>* get_down() const { return down; };
    void set_down(SkipNode<T>* new_node);
};

#endif