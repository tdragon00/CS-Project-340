#include "node.h"

Node::Node(std::string word)
{
    this->word = word;
}

Node::~Node()
{
    Node* current_node = this;
    while(this->next != nullptr)
    {
        this->prev = nullptr;
        current_node = this->next;
        this->next = nullptr;

        delete this;
    }
}

std::string Node::get_word()
{
    return this->word;
}
