#include <vector>
#include <time.h>

#include "skip_list.h"

static const int MAX_LEVELS = 5;

template <typename T>
SkipList<T>::SkipList()
{
    srand(time(nullptr));
    //int current_height;

    SkipNode<T>* new_head = new SkipNode<T>();
    priv_head = new_head;

    for (int i = 0; i < MAX_LEVELS; i++)
    {
        SkipNode<T>* new_level = new SkipNode<T>();

        new_head->set_down(new_level);
        new_level->set_up(new_head);

        new_head = new_level;
    }

    size = 0;
}

template <typename T>
SkipNode<T>* iter_to_layer(SkipNode<T>* &start, int level=0)
{
    SkipNode<T>* curr_node = start;
    int curr_level = level;
    while (curr_node->get_down() != nullptr && curr_level < MAX_LEVELS)
    {
        curr_node = curr_node->get_down();
        curr_level++;
    }

    return curr_node;
}

template <typename T>
SkipNode<T>* reverse_srch_up(SkipNode<T>* &start)
{
    // Searches for the nearest node with an up pointer in reverse order
    SkipNode<T>* curr_node = start;
    while (curr_node->get_up() == nullptr)
    {
        curr_node = curr_node->get_prev();
    }

    return curr_node;
}

template <typename T>
void SkipList<T>::insert(T data)
{
    SkipNode<T>* new_node = new SkipNode<T>(data);
    if (size == 0)
    {
        head = new_node;

        SkipNode<T>* prev_node = iter_to_layer(priv_head);
        head->set_prev(iter_to_layer(prev_node));
        prev_node->set_next(head);
        size++;

        return;
    }

    SkipNode<T>* insert_node = search(data, priv_head);

    // floor the node
    insert_node = iter_to_layer(insert_node);
    if (insert_node->get_prev() == nullptr)
    {
        if (insert_node->get_next() != nullptr)
        {
            SkipNode<T>* temp = insert_node->get_next();
            temp->set_prev(new_node);
            new_node->set_next(temp);
        }

        new_node->set_prev(insert_node);
        insert_node->set_next(new_node);
    }
    else if (new_node->get_data() > insert_node->get_data())
    {
        //cout << "INSERT: " << insert_node->get_data() << endl;
        if (insert_node->get_next() != nullptr)
        {
            SkipNode<T>* temp = insert_node->get_next();
            temp->set_prev(new_node);
            new_node->set_next(temp);
        }

        new_node->set_prev(insert_node);
        insert_node->set_next(new_node);
    }
    else
    {
        if (insert_node->get_prev() != nullptr)
        {
            SkipNode<T>* temp = insert_node->get_prev();
            temp->set_next(new_node);
            new_node->set_prev(temp);
        }

        new_node->set_next(insert_node);
        insert_node->set_prev(new_node);
    }

    // Should split this into a separate function
    SkipNode<T>* nearest_up_node = reverse_srch_up(new_node);
    int flip = flip_coin();
    int lvls_added = 0;
    SkipNode<T>* layer_node = new_node;
    while (flip != 0 && lvls_added < MAX_LEVELS - 1)
    {
        SkipNode<T>* clone_node = new SkipNode<T>(data);
        clone_node->set_down(layer_node);
        layer_node->set_up(clone_node);

        SkipNode<T>* up_node = nearest_up_node->get_up();
        if (up_node != nullptr)
        {
            SkipNode<T>* nxt_up_node = up_node->get_next();
            if (nxt_up_node != nullptr)
            {
                if (nxt_up_node->get_next() != nullptr)
                {
                    nxt_up_node->set_prev(clone_node);
                    clone_node->set_next(nxt_up_node);
                }
            }

            clone_node->set_prev(up_node);
            up_node->set_next(clone_node);
        }

        nearest_up_node = reverse_srch_up(up_node);
        flip = flip_coin();
        layer_node = clone_node;
        lvls_added++;

        cout << lvls_added <<" layer added" << endl;
    }

    if (insert_node->get_prev() == nullptr)
    {
        head = new_node;
    }
    else if (insert_node == head)
    {
        if (new_node->get_data() < head->get_data())
        {
            head = new_node;
        }
    }

    size++;
}

template <typename T>
SkipNode<T>* SkipList<T>::search(T data, SkipNode<T>* head, bool is_begin) const
{
    SkipNode<T>* curr_node = head;
    if (!is_begin)
    {
        if (curr_node->get_prev() != nullptr)
        {
            if (curr_node->get_data() == data && !is_begin)
            {
                return curr_node;
            }
        }
    }

    if (curr_node->get_next() == nullptr)
    {
        if (curr_node->get_down() != nullptr)
        {
            return this->search(data, curr_node->get_down(), is_begin);
        }
        else
        {
            return curr_node;
        }
    }

    // Check if we've reached the end of the private heads
    if (is_begin)
    {
        is_begin = false;
    }

    if (curr_node->get_next()->get_data() > data)
    {
        if (curr_node->get_down() != nullptr)
        {
            return this->search(data, curr_node->get_down(), is_begin);
        }
        else
        {
            return curr_node;
        }
    }
    else
    {
        return this->search(data, curr_node->get_next(), is_begin);
    }

    return curr_node;
}

template <typename T>
void SkipList<T>::pretty_print()
{
    SkipNode<T>* curr_layer = priv_head;
    SkipNode<T>* head_node = curr_layer->get_next();
    SkipNode<T>* depths;

    while (curr_layer != nullptr)
    {
        while (head_node != nullptr)
        {
            if (head_node != nullptr)
            {
                if(curr_layer->get_down() != nullptr)
                {
                    //tried to print stuff before got an endless loop
                    // //printing shit before
                    // depths = curr_layer->get_down();
                    // while (depths !=nullptr && depths->get_data() != head_node->get_data())
                    // {
                    // cout<<"---"<<endl;
                    // }
                    
                  
                }
                cout << head_node->get_data() << "-> ";
                head_node = head_node->get_next();
            }
        }

        cout << endl;
        if (curr_layer != nullptr)
        {
            curr_layer = curr_layer->get_down();

            if (curr_layer != nullptr)
            {
                head_node = curr_layer->get_next();
            }
        }
    }
}

template <typename T>
bool SkipList<T>::remove_node(T data)
{
    SkipNode<T>* key_node = search(data, priv_head);

    if (key_node->get_data() == data)
    {
        SkipNode<T>* base_node = iter_to_layer(key_node);

        remove_node(base_node);

        return true;
    }

    return false;
}

template <typename T>
bool SkipList<T>::remove_node(SkipNode<T>* node)
{
    SkipNode<T>* curr_node = node->get_up();

    // remove the bottom node first
    SkipNode<T>* next_node = node->get_next();
    SkipNode<T>* prev_node = node->get_prev();

    if (next_node != nullptr)
    {
        next_node->set_prev(prev_node);
    }

    if (prev_node != nullptr)
    {
        prev_node->set_next(next_node);
    }

    if (node->get_up() != nullptr)
    {
        while (curr_node->get_up() != nullptr)
        {
            next_node = curr_node->get_next();
            prev_node = curr_node->get_prev();

            if (next_node != nullptr)
            {
                next_node->set_prev(prev_node);
            }

            if (prev_node != nullptr)
            {
                prev_node->set_next(next_node);
            }

            SkipNode<T>* temp = curr_node;
            curr_node = curr_node->get_up();
            delete curr_node->get_down();
        }
    }
    else
    {
        delete curr_node;
    }


    this->size--;
    return true;
}

template<typename T>
void SkipList<T>::pop_front() {
    if (this->head == nullptr) {
        cout << "Cannot pop a node from an empty list." << endl;
        return;
    }

    if (this->head != nullptr && this->head->get_next() == nullptr) {
        SkipNode<T>* temp = this->head;
        this->head = nullptr;
        remove_node(temp);
    }
    else {
        SkipNode<T>* curr_head = this->head;
        while (curr_head->get_down() != nullptr) {
            curr_head = curr_head->get_down();
        }
        this->head = curr_head->get_next();
        remove_node(this->head->get_prev());
    }
}

template<typename T>
void SkipList<T>::pop_back() {

    if (this->head == nullptr) {
        cout << "Cannot pop a node from an empty list." << endl;
        return;
    }

    if (this->head != nullptr && this->head->get_next() == nullptr) {
        SkipNode<T>* temp = this->head;
        this->head = nullptr;
        remove_node(temp);
    }
    else {
        SkipNode<T>* curr = this->head;
        while (curr->get_next() != nullptr) {
            while (curr->get_down() != nullptr) {
                curr = curr->get_down();
            }
            curr = curr->get_next();
        }
        remove_node(curr);
    }
}

template <typename T>
int SkipList<T>::flip_coin()
{
    int face = rand() % 2;

    return face;
}