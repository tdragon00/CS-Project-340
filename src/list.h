#ifndef LIST_H
#define LIST_H

//node which is used for the list 
#include "node.h"

template <typename T>
class LinkedList {
private:
    Node<T>* head = nullptr;
    int size = 0;
public:
    LinkedList();//constructor
    ~LinkedList();//destructor
    LinkedList(Node<T>* head);//constructor with head node
    LinkedList(Node<T>* head, Node<T>* tail); //constructor with head and tail node
    void push_front(T data); //pushes data to the front of list
    void push_back(T data);  //pushes data to the back of the list
    void add_node(T data, Node<T>* specific_node);
    void add_node(Node<T> data, Node<T>* specific_node);
    Node<T>* find_node(T key) const;// linear search 
    Node<T>* find_mid_node() const; // finds the middle node of the list
    Node<T>* binary_find_node(T key, Node<T>*& lower_node, int high, int lower = 1) const;// binary search on the list
    bool remove_node(T key); //removes a node from the list via value
    bool remove_node(Node<T>* node); //removes a node from the list via node
    bool swap_node(Node<T>*& x, Node<T>*& y); //swaps two different nodes
    int length() const { return size; }; //returns size of list
    Node<T>* front() const { return head; }; //returns front of the list
    Node<T>* back() const; //returns the back of the list
    void pop_front();//returns the top node and removes it
    void pop_back(); //returns the last node and removes it 
};

#endif