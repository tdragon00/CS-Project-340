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

using namespace std;

struct Node
{
    string word;
    Node *next = nullptr;
    Node *prev = nullptr;

    Node(string word)
    {
        this->word = word;
    }

    string get_word()
    {
        return this->word;
    }
};

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

        if (key > mid_node->word)
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

void linear_sort(LinkedList* &list);
LinkedList* merge_sort(LinkedList* &list);
LinkedList* merge_dicts(LinkedList* list_1, LinkedList* list_2);
void add_to_dict(LinkedList* &list, Node* node);
void sort_dicts(LinkedList* &list, Node* node_1, Node* node_2);

int main()
{
    cout << "Hello dlrow" << endl;
}

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
