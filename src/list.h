#include <string>

#include "node.h"

using namespace std;

class LinkedList {
public:
	Node* head = nullptr;
	int size = 0;

	LinkedList();
	~LinkedList();
	LinkedList(Node* head);
	LinkedList(Node* head, Node* tail);
	void add_node(string content);
	void add_node(string content, bool add_to_end);
	void add_node(string content, Node* specific_node);
	void add_node(Node content, Node* specific_node);
	Node* find_node(string key);
	Node* find_mid_node();
	Node* binary_find_node(string key, Node*& lower_node, int high, int lower = 1);
	void deconstruct();
	bool remove_node(string key);
	bool remove_node(Node* node);
	bool swap_node(Node*& x, Node*& y);
};