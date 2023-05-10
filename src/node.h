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
    Node(T data); //constructor with data
    ~Node(); //destructor
    T get_data() const; //getter
    void set_data(T data); //setter

    Node<T>* get_next() const; //getts the next node can return null
    void set_next(Node* newNode); //sets the next node not nullsafe
    Node<T>* get_prev() const; // gets the previous node can return null
    void set_prev(Node* newNode); //sets the previous node not nullsafe
};
#endif