/*
 Overview:
  This is an implementation of a Linked List, specifically for a string data type.
  Initialization is done by calling `new` with the LinkedList struct.

 Structure specifications:
  Linked List:
    `int size` - the size of the list.
    `Node* head` - The current head node of the list
  Node:
     `Node *next` - a pointer that points to the next node
     `Node *prev` - a pointer that points to the previous node
     `string word` - The content of the node

 Considerations:
  By default, when adding a new node, the head of the linked list becomes the new node
  when the node is added. This can be overriden by the function overload of the `add_node`
  function.

 Notable functions:
  `LinkedList()` - The default constructor for the linked list. Initializes head as null.
  and the size to 0.
  `LinkedList(Node* head, Node* tail)` - Create a linked list from a specific node to an end
  (assuming the tail is connected to the head)
  `add_node(string content)` - Adds a new node to the list.
  `add_node(string content, Node* specific_node) - Add a new node at a specific 'index' of
  the linked list.
  `add_node(string content, bool add_to_end)` - Add a new node at the end of the linked list
  while retaining the current head of the list
  `Node* find_node(string content)` - Find a specific node via linear search. Content is the
  keyword to search for. Returns the node if found, nullptr if the not found.
  `bool remove_node(string content)` - Removes a node via a specific key. Returns true if the
  remove succeeds. False if the Node has not been found.
  `Node* find_mid_node() - Returns the middle node of the list`
  `deconstruct()` - deletes every node and the list itself.
*/

#include <string>
#include <iostream>
#include <vector>


#include "list.h"
#include "list.cpp"

#include "skip_list.h"
#include "skip_list.cpp"

#include "node.h"

using namespace std;

/*
NOTE: We don't really need these right now,
void linear_sort(LinkedList* &list);
LinkedList* merge_sort(LinkedList* &list);
LinkedList* merge_dicts(LinkedList* list_1, LinkedList* list_2);
void add_to_dict(LinkedList* &list, Node* node);
void sort_dicts(LinkedList* &list, Node* node_1, Node* node_2);

*/

template <typename T>
void print(LinkedList<T> &list);

int main()
{
    LinkedList<string> test = LinkedList<string>();

    test.push_front("hi");
    test.push_front("ww");

    Node<string>* head = test.front();
    cout << head->get_data() << endl;

    Node<string>* test_node = test.binary_find_node("hi", head, test.length());

    if (test_node != nullptr)
    {
        cout << test_node->get_data() << endl;

        test_node->set_data("wassup");
    }

    cout << "Hello dlrow" << endl;

    print(test);

    SkipList test2 = SkipList<string>();

    test2.insert("XDDD");
    test2.insert("ABC");
    test2.insert("abc");
    test2.insert("DEF");
    test2.insert("ZXY");
    test2.insert("ZXY");

    // Temporary print testing
    cout << test2.front()->get_data() << endl;
    cout << test2.front()->get_next()->get_data() << endl;
    cout << test2.front()->get_next()->get_next()->get_data() << endl;
    cout << test2.front()->get_next()->get_next()->get_next()->get_data() << endl;
    cout << test2.front()->get_next()->get_next()->get_next()->get_next()->get_data() << endl;

    test2.pretty_print();
}

template <typename T>
void print(LinkedList<T> &list) 
{
    Node<T>* iter = list.front();
    for (int i = 0; i < list.length(); i++) 
    {
        cout << iter->get_data() << endl;
        iter = iter->get_next();
    }
}

/*
void linear_sort(LinkedList* &list)
{
    Node* iter_node = list->head;

    while(iter_node != nullptr)
    {
        Node* smallest_node = iter_node;
        Node* current_node = iter_node->next;

        while(current_node != nullptr)
        {
            if (current_node->get_word() < smallest_node->get_word())
            {
                smallest_node = current_node;
            }

            current_node = current_node->next;
        }

        if (smallest_node != iter_node)
        {
            list->swap_node(smallest_node, iter_node);
        }
        iter_node = iter_node->next;
    }
}

LinkedList* merge_sort(LinkedList* &list)
{
    if (list->head->next == nullptr || list->size == 1)
    {
    //  cout << "start: " << list->head->get_word() << "\tend: " << list->head->get_word() << endl;
        return list;
    }

    Node* mid_node = list->find_mid_node();
    Node* end_node = mid_node->next;
    LinkedList* left_list;
    LinkedList* right_list;


    if (end_node != nullptr)
    {
        while(end_node->next != nullptr)
        {
            end_node = end_node->next;
        }
    }

    // If there is only 2 nodes in the list,
    // create 2 lists only containing one node each
    if (list->head->next->next == nullptr)
    {
        left_list = new LinkedList(mid_node->prev);
        right_list = new LinkedList(mid_node);
    }
    else
    {
        // Create the right half, from the next node to mid to the end
        // if there is nothing to the right of mid, create an empty list
        if (list->find_mid_node()->next != nullptr)
        {
            right_list = new LinkedList(list->find_mid_node()->next, end_node);
        }
        else
        {
            right_list = new LinkedList();
        }

        left_list = new LinkedList(list->head, mid_node);
    }

    // cout << "start: " << list->head->get_word() << "\tend: " << end_node->get_word() << endl;

    LinkedList* left_half = merge_sort(left_list);
    LinkedList* right_half = merge_sort(right_list);

    return merge_dicts(left_half, right_half);
}

LinkedList* merge_dicts(LinkedList* list_1, LinkedList* list_2)
{
    LinkedList* new_list = new LinkedList();

    Node* current_node_1 = list_1->head;
    Node* current_node_2 = list_2->head;

    while (current_node_1 != nullptr || current_node_2 != nullptr)
    {
        Node* temp_1 = nullptr; Node* temp_2 = nullptr;

        if (current_node_1 != nullptr)
        {
            temp_1 = current_node_1->next;
        }

        if (current_node_2 != nullptr)
        {
            temp_2 = current_node_2->next;
        }

        sort_dicts(new_list, current_node_1, current_node_2);

        current_node_1 = temp_1;
        current_node_2 = temp_2;

        if (current_node_1 != nullptr)
        {
            list_1->remove_node(current_node_1->prev);
        }

        if (current_node_2 != nullptr)
        {
            list_2->remove_node(current_node_2->prev);
        }
    }

    list_1->deconstruct();
    list_2->deconstruct();

    return new_list;
}

void sort_dicts(LinkedList* &list, Node* node_1, Node* node_2)
{
    add_to_dict(list, node_1);
    add_to_dict(list, node_2);
}

void add_to_dict(LinkedList* &list, Node* node)
{
    Node* current_node = list->head;
    if (node != nullptr)
    {
        if (node->get_word().size() > 0)
        {
            if (current_node != nullptr)
            {
                while (current_node != nullptr)
                {
                    if (current_node != nullptr)
                    {
                        if (current_node->get_word() > node->get_word())
                        {
                            break;
                        }
                    }

                    current_node = current_node->next;
                }
            }

            if (list->size > 0)
            {
                if (current_node != nullptr)
                {
                    if (current_node->prev != nullptr)
                    {
                        if (current_node->prev->get_word() != node->get_word())
                        {
                            list->add_node(*node, current_node);
                        }
                    }
                    else
                    {
                        if (current_node->next != nullptr)
                        {
                            if (current_node->next->get_word() != node->get_word())
                            {
                                list->add_node(*node, current_node);
                            }
                        }
                        else
                        {
                            if (current_node->get_word() != node->get_word())
                            {
                                list->add_node(*node, current_node);
                            }
                        }
                    }
                }
                else
                {
                    Node* end_check = list->binary_find_node(node->get_word(), list->head, list->size);

                    if (end_check != nullptr)
                    {
                        if (end_check->get_word() != node->get_word())
                        {
                            list->add_node(node->get_word(), true);
                        }
                    }
                    else
                    {
                        list->add_node(node->get_word(), true);
                    }
                }
            }
            else
            {
                list->add_node(node->get_word());
            }
        }
    }
}
*/