#include <string>
#include <iostream>
#include <vector>

#include "node.h"

using namespace std;

struct LinkedList
{
    Node *head = nullptr;
    int size = 0;

    LinkedList()
    {
        this->head = nullptr;
        this->size = 0;
    }

    LinkedList(Node* head)
    {
        this->head = head;
        head->prev = nullptr;
        head->next = nullptr;

        this->size = 1;
    }

    LinkedList(Node* head, Node* tail)
    {
        head->prev = nullptr;
        this->head = head;
        tail->next = nullptr;
        this->size = 1;

        if (this->head != tail && this->head->next != nullptr)
        {
            Node* counter = this->head->next;
            while(counter->next != nullptr)
            {
                this->size++;
                counter = counter->next;
            }
        }

    }

    void add_node(string content)
    {
        Node *new_node = new Node(content);
        if (this->head != nullptr)
        {
            this->head->prev = new_node;
        }

        new_node->next = this->head;
        new_node->prev = nullptr;

        this->head = new_node;
        this->size++;
    }

    void add_node(string content, bool add_to_end)
    {
        if (add_to_end)
        {
            Node *current_node = this->head;
            Node *new_node = new Node(content);
            new_node->next = nullptr;

            if (current_node == nullptr)
            {
                this->head = new_node;
                this->head->prev = nullptr;
                this->size++;

                return;
            }

            Node* last_node = this->head;
            while(last_node->next != nullptr)
            {
                last_node = last_node->next;
            }

            last_node->next = new_node;
            new_node->prev = last_node;
            this->size++;
        }
    }

    void add_node(string content, Node *specific_node)
    {
        Node *next_node = specific_node->next;
        Node *new_node = new Node(content);

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

    void add_node(Node content, Node *specific_node)
    {
        Node *new_node = new Node(content.get_word());

        if (specific_node == nullptr)
        {
            new_node->next = this->head;
            new_node->prev = nullptr;

            this->head = new_node;
            this->size++;

            return;
        }

        Node *previous_node = specific_node->prev;
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
    Node *find_node(string key)
    {
        Node *curr_node = this->head;
        while (curr_node != nullptr)
        {
            if (curr_node->get_word() == key)
            {
                break;
            }

            curr_node = curr_node->next;
        }

        return curr_node;
    }

    Node* find_mid_node()
    {
        Node* mid_node = this->head;
        Node* fast_ptr = this->head;

        while(fast_ptr != nullptr && fast_ptr->next != nullptr)
        {
            mid_node = mid_node->next;
            fast_ptr = fast_ptr->next->next;
        }

        return mid_node;
    }

    Node *binary_find_node(string key, Node* &lower_node, int high, int lower=1)
    {
        if (key == lower_node->get_word())
        {
            return lower_node;
        }

        int mid = ((high - lower) / 2) + lower;
        int i = lower;

        Node* mid_node = this->find_mid_node();

        i = mid;
        Node* high_node = mid_node;

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
            if (high_node->get_word() == lower_node->get_word())
            {
                return nullptr;
            }
        }

        if (mid_node->get_word() == lower_node->get_word())
        {
            return nullptr;
        }

        if (key == mid_node->get_word())
        {
            return mid_node;
        }

        if (key == high_node->get_word())
        {
            return high_node;
        }

        if (key > mid_node->get_word())
        {
            mid_node = this->binary_find_node(key, mid_node->next, high - 1, mid + 1);
        }
        else
        {
            mid_node = this->binary_find_node(key, lower_node->next, mid - 1, lower + 1);
        }

        return mid_node;
    }

    void deconstruct()
    {
        Node *current_node = this->head;

        while (current_node != nullptr)
        {
            Node *next = current_node->next;
            delete current_node;
            current_node = next;
        }

        delete this;
    }

    bool remove_node(string key)
    {
        Node *key_node = this->find_node(key);
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

    bool remove_node(Node* node)
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

    bool swap_node(Node* &x, Node* &y)
    {
        Node* deref_y = y;
        Node* deref_x = x;

        // If the two node's datas are the same, no need to swap.
        if (deref_y->get_word() == deref_x->get_word())
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
        Node* temp = deref_x->next;
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
};
