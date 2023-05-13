//node class for our linked list project
#ifndef NODE_H
#define NODE_H
template<typename T>
class Node
{
private:
    T* data; // data
    Node* next = nullptr; //pointer to next node
    Node* prev = nullptr; //pointer to previous node
public:
    Node();
    Node(T data); //constructor with data
    ~Node(); //destructor
    T get_data() const; //getter
    void set_data(T data); //setter

    Node<T>* get_next() const; //getts the next node can return null
    void set_next(Node* newNode); //sets the next node not nullsafe
    Node<T>* get_prev() const; // gets the previous node can return null
    void set_prev(Node* newNode); //sets the previous node not nullsafe
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