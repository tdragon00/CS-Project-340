/*
This is a linked list cpp this inculdes the implementation for all functions built for
the linked list.


*/
//#include <string>
//#include <iostream>
//#include <vector>
#include "node.h"
#include "node.cpp"
#include "list.h"
using namespace std;

//default constructor
template <typename T>
LinkedList<T>::LinkedList() {
    this->head = nullptr;
    this->size = 0;
}

//constructor with head node
template <typename T>
LinkedList<T>::LinkedList(Node<T>* head)
{
    this->head = head;
    head->set_prev(nullptr);
    head->set_next(nullptr);

    this->size = 1;
}


//potential scope issue
//constructor with head and tail node
template <typename T>
LinkedList<T>::LinkedList(Node<T>* head, Node<T>* tail)
{
    head->set_prev(nullptr);
    this->head = head;
    tail->set_next(nullptr);
    this->size = 1;

    if (this->head != tail && this->head->get_next() != nullptr)
    {
        Node<T>* counter = this->head->get_next();
        while (counter->get_next() != nullptr)
        {
            this->size++;
            counter = counter->get_next();
        }
    }

}

//desstructor
template <typename T>
LinkedList<T>::~LinkedList()
{
    // Should start a chain delete throughout the list
    while (head->get_next() != nullptr)
    {
        head = head->get_next();
        delete head->get_prev();
    }

    delete this->head;
}

//this function pushes data to the front of the list.
template <typename T>
void LinkedList<T>::push_front(T data)
{

    //cout << "push_front called";
    Node<T>* new_node = new Node<T>(data);
    if (this->head != nullptr)
    {
        this->head->set_prev(new_node);
    }

    new_node->set_next(this->head);
    new_node->set_prev(nullptr);

    this->head = new_node;
    this->size++;
}

//this function pushes a data node to the back of the list.
template <typename T>
void LinkedList<T>::push_back(T data)
{
   
    
        Node<T>* current_node = this->head;
        Node<T>* new_node = new Node<T>(data);
        new_node->set_next(nullptr);

        if (current_node == nullptr)
        {
            this->head = new_node;
            this->head->set_prev(nullptr);
            this->size++;

            return;
        }

        Node<T>* last_node = this->head;
        while (last_node->get_next() != nullptr)
        {
            last_node = last_node->get_next();
        }

        last_node->set_next(new_node);
        new_node->set_prev(last_node);
        this->size++;
    
}

//inserts a a new node after a specific node.
template <typename T>
void LinkedList<T>::add_node(T data, Node<T>* specific_node)
{
    Node<T>* next_node = specific_node->get_next();
    Node<T>* new_node = new Node<T>(data);

    if (next_node == nullptr)
    {
        specific_node->set_next(new_node);
    }
    else
    {
        next_node->set_next(new_node);
    }

    new_node->set_prev(specific_node);
    new_node->set_next(next_node);
    this->size++;
}

//inserts a node after a specific node.
template <typename T>
void LinkedList<T>::add_node(Node<T> data, Node<T>* specific_node)
{
    Node<T>* new_node = new Node<T>(data.get_data());

    if (specific_node == nullptr)
    {
        new_node->set_next(this->head);
        new_node->set_prev(nullptr);

        this->head = new_node;
        this->size++;

        return;
    }

    Node<T>* previous_node = specific_node->get_prev();
    if (previous_node == nullptr)
    {
        this->head = new_node;
    }
    else
    {
        previous_node->set_next(new_node);
    }

    new_node->set_next(specific_node);
    specific_node->set_prev(new_node);
    new_node->set_prev(previous_node);
    this->size++;
}

// Just a linear search to find the specific node
template <typename T>
Node<T>* LinkedList<T>::find_node(T key) const
{
    Node<T>* curr_node = this->head;
    while (curr_node != nullptr)
    {
        if (curr_node->get_data() == key)
        {
            break;
        }

        curr_node = curr_node->get_next();
    }

    return curr_node;
}

//this finds the middle node of the list
template <typename T>
Node<T>* LinkedList<T>::find_mid_node() const
{
    Node<T>* mid_node = this->head;
    Node<T>* fast_ptr = this->head;

    while (fast_ptr != nullptr && fast_ptr->get_next() != nullptr)
    {
        mid_node = mid_node->get_next();
        fast_ptr = fast_ptr->get_next()->get_next();
    }

    return mid_node;
}

//this is a binary search to find an item in the list. requires find mid node to be implemented
template <typename T>
Node<T>* LinkedList<T>::binary_find_node(T key, Node<T>*& lower_node, int high, int lower) const
{
    if (key == lower_node->get_data())
    {
        return lower_node;
    }

    int mid = ((high - lower) / 2) + lower;
    int i = lower;

    Node<T>* mid_node = this->find_mid_node();

    i = mid;
    Node<T>* high_node = mid_node;

    while (i < high)
    {
        if (high_node->get_next() == nullptr)
        {
            break;
        }
        high_node = high_node->get_next();
        i++;
    }

    if (lower > high)
    {
        return nullptr;
    }

    if (high_node != nullptr)
    {
        if (high_node->get_data() == lower_node->get_data())
        {
            return nullptr;
        }
    }

    if (mid_node->get_data() == lower_node->get_data())
    {
        return nullptr;
    }

    if (key == mid_node->get_data())
    {
        return mid_node;
    }

    if (key == high_node->get_data())
    {
        return high_node;
    }

    Node<T>* ref_node;
    if (key > mid_node->get_data())
    {
        ref_node = mid_node->get_next(); 
        mid_node = this->binary_find_node(key, ref_node, high - 1, mid + 1);
    }
    else
    {
        ref_node = lower_node->get_next(); 
        mid_node = this->binary_find_node(key, ref_node, mid - 1, lower + 1);
    }

    return mid_node;
}

//this removes a node from the list via data
template <typename T>
bool LinkedList<T>::remove_node(T key)
{
    Node<T>* key_node = this->find_node(key);
    bool result = false;

    if (key_node != nullptr)
    {
        if (key_node == this->head)
        {
            this->head = key_node->get_next();
            key_node->set_prev(nullptr);
        }
        else
        {
            key_node->get_prev()->set_next(key_node->get_next());
        }

        delete key_node;
        this->size--;

        result = true;
    }

    return result;
}

//this removes a node from the list via node
template <typename T>
bool LinkedList<T>::remove_node(Node<T>* node)
{
    bool result = false;
    if (node != nullptr)
    {
        if (node == this->head)
        {
            this->head = this->head->get_next();
            node->set_prev(nullptr);
        }
        else
        {
            node->get_prev()->set_next(node->get_next());
        }

        delete node;
        this->size--;

        result = true;
    }

    return result;
}
//this function swaps two nodes
template <typename T>
bool LinkedList<T>::swap_node(Node<T>*& x, Node<T>*& y)
{
    Node<T>* deref_y = y;
    Node<T>* deref_x = x;

    // If the two node's datas are the same, no need to swap.
    if (deref_y->get_data() == deref_x->get_data())
    {
        return false;
    }

    // Check if the either nodes are the head, then set
    // the other node to head
    if (deref_x->get_prev() == nullptr)
    {
        this->head = deref_y;
    }
    else if (deref_y->get_prev() == nullptr)
    {
        this->head = deref_x;
    }

    // Set each node's next to the other node's next.
    Node<T>* temp = deref_x->get_next();
    deref_x->set_next(deref_y->get_next());
    deref_y->set_next(temp);

    if (deref_x->get_next() != nullptr)
    {
        deref_x->get_next()->set_prev(deref_x);
    }

    if (deref_y->get_next() != nullptr)
    {
        deref_y->get_next()->set_prev(deref_y);
    }

    // Set the node's previous nodes to the swapped nodes.
    temp = deref_x->get_prev();
    deref_x->set_prev(deref_y->get_prev());
    deref_y->set_prev(temp);

    if (deref_x->get_prev() != nullptr)
    {
        deref_x->get_prev()->set_next(deref_x);
    }

    if (deref_y->get_prev() != nullptr)
    {
        deref_y->get_prev()->set_next(deref_y);
    }

    // There is a weird zybooks quirk, where you have to manually
    // reassign dereferences back
    x = deref_y;
    y = deref_x;

    return true;
}

//returns the last node
template<typename T>
Node<T>* LinkedList<T>::back() const
{

    Node<T>* iterNode = this->head;

    while (iterNode->get_next() != nullptr) { // Use iterNode pointer to traverse to the end of the list
        iterNode = iterNode->get_next();
    }

    return iterNode;
}

//returns the top node and removes it.
template <typename T>
void LinkedList<T>::pop_front() 
{

    if (this->head == nullptr)
    {
        cout << "Cannot pop a node from an empty list." << endl;
    }
    else 
    {
        Node<T>* temp = this->head;

        if ((this->head != nullptr) && (this->head->get_next() == nullptr)) 
        { // Popping the node of list that only containts one node.
            this->head = nullptr;
            temp = nullptr;
            delete temp;
            this->size--;
        }
        else 
        {                                // If the head node of the list is not a null pointer, create a
            this->head = this->head->get_next();    // temp node pointer variable to hold the information of the current
            temp = nullptr;                   // head node and set the next node of the current head node to new head node. 
            delete temp;                      // Set the previous node of the new head node (old head node) to null pointer,
            this->size--;                     // and delete the old head node. Also, decrease the size of the list by 1.
        }
    }
}

//returns the last node and removes it from the list.
template <typename T>
void LinkedList<T>::pop_back() 
{

    if (this->head == nullptr) 
    {
        cout << "Cannot pop a node from an empty list." << endl;
    }
    else 
    {
        Node<T>* temp = this->head;

        if ((this->head != nullptr) && (this->head->get_next() == nullptr))
        {
            this->head = nullptr;
            temp = nullptr;
            delete temp;
            this->size--;
        }
        else 
        {
            while (temp->get_next() != nullptr)
            {
                temp = temp->get_next();
            }
            temp->get_prev()->set_next(nullptr);
            temp = nullptr;
            delete temp;
            this->size--;
        }
    }
}
