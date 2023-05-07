#include <vector>
#include <time.h>

#include "skip_list.h"

static const int MAX_LEVELS = 5;

template <typename T>
SkipList<T>::SkipList()
{
    srand(time(nullptr));

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
SkipNode<T>* iter_to_bottom(SkipNode<T>* &start)
{
    SkipNode<T>* curr_node = start;
    while (curr_node->get_down() != nullptr)
    {
        curr_node = curr_node->get_down();
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

        SkipNode<T>* prev_node = iter_to_bottom(priv_head);
        head->set_prev(iter_to_bottom(prev_node));
        prev_node->set_next(head);
        size++;

        return;
    }

    SkipNode<T>* insert_node = search(data, priv_head);

    if (new_node->get_data() > insert_node->get_data())
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
    else
    {
        if (insert_node->get_prev() != nullptr)
        {
            SkipNode<T>* temp = insert_node->get_prev();
            if (temp->get_prev() != nullptr)
            {
                SkipNode<T>* prev_temp = temp->get_prev();
                prev_temp->set_next(new_node);
                new_node->set_prev(prev_temp);
            }
            temp->set_next(new_node);
            new_node->set_prev(temp);
        }

        new_node->set_next(insert_node);
        insert_node->set_prev(new_node);
    }

    // TODO: add levels to node via coin flip
    if (insert_node == head)
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

    if (curr_node->get_next() == nullptr)
    {
        if (curr_node->get_down() != nullptr)
        {
            return this->search(data, curr_node->get_down());
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
        curr_node = curr_node->get_next();
    }

    if (curr_node->get_data() == data)
    {
        return curr_node;
    }
    else if (curr_node->get_next() != nullptr)
    {
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
    }
    else
    {
        if (curr_node->get_next() == nullptr)
        {
            return curr_node;
        }
        return this->search(data, curr_node->get_next(), is_begin);
    }

    return curr_node;
}

template <typename T>
int SkipList<T>::flip_coin()
{
    int face = rand() % 2;

    cout << face << endl;
    return face;
}