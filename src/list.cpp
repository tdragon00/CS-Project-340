#include <string>
#include <iostream>
#include <vector>

#include "node.h"
#include "node.cpp"

#include "list.h"

using namespace std;

template <typename T>
LinkedList<T>::LinkedList() {
    this->head = nullptr;
    this->size = 0;
}

template <typename T>
LinkedList<T>::LinkedList(Node<T>* head)
{
    this->head = head;
    head->prev = nullptr;
    head->next = nullptr;

    this->size = 1;
}


//potential scope issue
template <typename T>
LinkedList<T>::LinkedList(Node<T>* head, Node<T>* tail)
{
    head->prev = nullptr;
    this->head = head;
    tail->next = nullptr;
    this->size = 1;

    if (this->head != tail && this->head->next != nullptr)
    {
        Node<T>* counter = this->head->next;
        while (counter->next != nullptr)
        {
            this->size++;
            counter = counter->next;
        }
    }

}

//desstructor
template <typename T>
LinkedList<T>::~LinkedList()
{
    // Should start a chain delete throughout the list
    while (head->next != nullptr)
    {
        head = head->next;
        delete head->prev;
    }

    delete this->head;
}

template <typename T>
void LinkedList<T>::push_front(T data)
{

    cout << "push_front called";
    Node<T>* new_node = new Node<T>(data);
    if (this->head != nullptr)
    {
        this->head->prev = new_node;
    }

    new_node->next = this->head;
    new_node->prev = nullptr;

    this->head = new_node;
    this->size++;
}

template <typename T>
void LinkedList<T>::add_node(T data, bool add_to_end)
{
    if (add_to_end)
    {
        Node<T>* current_node = this->head;
        Node<T>* new_node = new Node<T>(data);
        new_node->next = nullptr;

        if (current_node == nullptr)
        {
            this->head = new_node;
            this->head->prev = nullptr;
            this->size++;

            return;
        }

        Node<T>* last_node = this->head;
        while (last_node->next != nullptr)
        {
            last_node = last_node->next;
        }

        last_node->next = new_node;
        new_node->prev = last_node;
        this->size++;
    }
}

template <typename T>
void LinkedList<T>::add_node(T data, Node<T>* specific_node)
{
    Node<T>* next_node = specific_node->next;
    Node<T>* new_node = new Node<T>(data);

    if (next_node == nullptr)
    {
        specific_node->next = new_node;
    }
    else
    {
        next_node->next = new_node;
    }

    new_node->prev = specific_node;
    new_node->next = next_node;
    this->size++;
}

template <typename T>
void LinkedList<T>::add_node(Node<T> data, Node<T>* specific_node)
{
    Node<T>* new_node = new Node<T>(data.get_data());

    if (specific_node == nullptr)
    {
        new_node->next = this->head;
        new_node->prev = nullptr;

        this->head = new_node;
        this->size++;

        return;
    }

    Node<T>* previous_node = specific_node->prev;
    if (previous_node == nullptr)
    {
        this->head = new_node;
    }
    else
    {
        previous_node->next = new_node;
    }

    new_node->next = specific_node;
    specific_node->prev = new_node;
    new_node->prev = previous_node;
    this->size++;
}

// Just a linear search to find the specific node
template <typename T>
Node<T>* LinkedList<T>::find_node(T key)
{
    Node<T>* curr_node = this->head;
    while (curr_node != nullptr)
    {
        if (curr_node->get_data() == key)
        {
            break;
        }

        curr_node = curr_node->next;
    }

    return curr_node;
}

template <typename T>
Node<T>* LinkedList<T>::find_mid_node()
{
    Node<T>* mid_node = this->head;
    Node<T>* fast_ptr = this->head;

    while (fast_ptr != nullptr && fast_ptr->next != nullptr)
    {
        mid_node = mid_node->next;
        fast_ptr = fast_ptr->next->next;
    }

    return mid_node;
}

template <typename T>
Node<T>* LinkedList<T>::binary_find_node(T key, Node<T>* &lower_node, int high, int lower)
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
        if (high_node->next == nullptr)
        {
            break;
        }
        high_node = high_node->next;
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

    if (key > mid_node->get_data())
    {
        mid_node = this->binary_find_node(key, mid_node->next, high - 1, mid + 1);
    }
    else
    {
        mid_node = this->binary_find_node(key, lower_node->next, mid - 1, lower + 1);
    }

    return mid_node;
}

template <typename T>
bool LinkedList<T>::remove_node(T key)
{
    Node<T>* key_node = this->find_node(key);
    bool result = false;

    if (key_node != nullptr)
    {
        if (key_node == this->head)
        {
            this->head = key_node->next;
            key_node->prev = nullptr;
        }
        else
        {
            key_node->prev->next = key_node->next;
        }

        delete key_node;
        this->size--;

        result = true;
    }

    return result;
}

template <typename T>
bool LinkedList<T>::remove_node(Node<T>* node)
{
    bool result = false;
    if (node != nullptr)
    {
        if (node == this->head)
        {
            this->head = this->head->next;
            node->prev = nullptr;
        }
        else
        {
            node->prev->next = node->next;
        }

        delete node;
        this->size--;

        result = true;
    }

    return result;
}

template <typename T>
bool LinkedList<T>::swap_node(Node<T>* &x, Node<T>* &y)
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
    if (deref_x->prev == nullptr)
    {
        this->head = deref_y;
    }
    else if (deref_y->prev == nullptr)
    {
        this->head = deref_x;
    }

    // Set each node's next to the other node's next.
    Node<T>* temp = deref_x->next;
    deref_x->next = deref_y->next;
    deref_y->next = temp;

    if (deref_x->next != nullptr)
    {
        deref_x->next->prev = deref_x;
    }

    if (deref_y->next != nullptr)
    {
        deref_y->next->prev = deref_y;
    }

    // Set the node's previous nodes to the swapped nodes.
    temp = deref_x->prev;
    deref_x->prev = deref_y->prev;
    deref_y->prev = temp;

    if (deref_x->prev != nullptr)
    {
        deref_x->prev->next = deref_x;
    }

    if (deref_y->prev != nullptr)
    {
        deref_y->prev->next = deref_y;
    }

    // There is a weird zybooks quirk, where you have to manually
    // reassign dereferences back
    x = deref_y;
    y = deref_x;

    return true;
}