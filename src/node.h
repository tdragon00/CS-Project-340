#include <string>

class Node
{
    std::string word;
public:
    Node *next = nullptr;
    Node *prev = nullptr;

    Node(std::string word);
    std::string get_word();
};
