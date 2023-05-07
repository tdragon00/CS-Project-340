#include <vector>
#include <time.h>

#include "skip_list.h"

static const int MAX_LEVELS = 5;

template <typename T>
SkipList<T>::SkipList()
{
    srand(time(nullptr));

    size = 0;
}

template <typename T>
void SkipList<T>::insert(T data)
{
    // If size is 0, then initialize 
    // of every lane. the first node as the head
    if (size == 0)
    {
        SkipNode<T>* new_head = new SkipNode<T>(data);
        for (int i = 0; i < MAX_LEVELS; i++)
        {
            SkipNode<T>* new_level = new SkipNode<T>(data);

            new_level->set_down(new_head);
            new_head = new_level;
        }

        head = new_head;

        size++;

        return;
    }
}

template <typename T>
int SkipList<T>::flip_coin()
{
    int face = rand() % 2;

    cout << face << endl;
    return face;
}