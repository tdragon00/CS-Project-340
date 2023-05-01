#include "node.h"

Node::Node(std::string word)
{
    this->word = word;
}

std::string Node::get_word()
{
    return this->word;
}
