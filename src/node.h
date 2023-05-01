#include <string>

struct Node
{
    std::string word;
    Node *next = nullptr;
    Node *prev = nullptr;

    Node(std::string word)
    {
        this->word = word;
    }

    std::string get_word()
    {
        return this->word;
    }
};
