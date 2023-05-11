#include <string>
#include <iostream>
#include "list.h"
#include "list.cpp"

using namespace std;

void print(LinkedList<string>& userList) {
	Node<string>* curr = userList.front();

	while (curr != nullptr) {
		cout << curr->get_data() << endl;
		curr = curr->get_next();
	}

	delete curr;
}


int main() {
	LinkedList<string> list;
	Node<string>* wordFound;

	cout << "Creating a LinkedList of string data type with the words: apple, banana, cherry, dewberry, elderberry, fig." << endl;
	cout << "list.push_back(\"banana\");" << endl;
	cout << "list.push_front(\"elderberry\");" << endl;
	cout << "list.push_front(\"cherry\");" << endl;
	cout << "list.push_back(\"apple\");" << endl;
	cout << "list.push_front(\"fig\");" << endl;
	cout << "list.push_back(\"dewberry\");" << endl;
	cout << endl;

	list.push_back("banana");
	list.push_front("elderberry");
	list.push_front("cherry");
	list.push_back("apple");
	list.push_front("fig");
	list.push_back("dewberry");

	cout << "After calling push_front() and push_back() to add words into the list. \nExpected result:" << endl;
	cout << "fig \ncherry \nelderberry \nbanana \napple \ndewberry" << endl;
	cout << endl;

	cout << "Actual result:" << endl;
	print(list);
	cout << "------------------------------------------------------------------------------" << endl;
	cout << endl;



	cout << "Finding the node contains the word \"banana\" in the LinkedList using the linear search function called find_node()." << endl;
	cout << "The function will return a node pointer that points to that node. We can use get_data() to get the word that was stored in that node." << endl;
	cout << "Expected result:" << endl;
	cout << "banana" << endl;
	cout << endl;

	wordFound = list.find_node("banana");
	cout << "Actual result: " << endl;
	cout << wordFound->get_data() << endl;
	cout << "------------------------------------------------------------------------------" << endl;
	cout << endl;



	cout << "Finding the node contains the word \"orange\" in the LinkedList using the linear search function called find_node()." << endl;
	cout << "The function will return a node pointer that points to that node. We can use get_data() to get the word that was stored in that node." << endl;
	cout << "Since the word \"orange\" is not in the LinkedList, the function will return a null pointer. We can check that with an if-statement" << endl;
	cout << "If the returned node pointer is a null pointer, we can output \"The word \"orange\" is not in the list.\". Otherwise, we output the word of the node." << endl;
	cout << "Expected result:" << endl;
	cout << "The word \"orange\" is not in the list." << endl;
	cout << endl;

	wordFound = list.find_node("orange");
	cout << "Actual result: " << endl;
	if (wordFound == nullptr) {
		cout << "The word \"orange\" is not in the list." << endl;
	}
	else {
		cout << wordFound->get_data() << endl;
	}
	cout << "------------------------------------------------------------------------------" << endl;
	cout << endl;


	/*	cout << "Adding a node to the LinkedList." << endl;
		list.add_node("grapes", list.find_node("banana"));
		cout << "-After calling list.add_node(\"grapes\"), list.find_node(\"banana\"); \nExpected result:" << endl;
		cout << "fig \ncherry \nelderberry \ngrapes \nbanana \napple \ndewberry" << endl;
		cout << endl;

		cout << "Acutual result:" << endl;
		print(list);
		cout << "------------------------------------------------------------------------------" << endl;
		cout << endl;*/


	cout << "Adding a node to the LinkedList." << endl;
	cout << "We create a newNode variable with the word \"orange\" and call the function add_node(newNode, list.find_node(\"banana\")) \nExpected result:" << endl;
	cout << "fig \ncherry \nelderberry \norange \nbanana \napple \ndewberry" << endl;
	cout << endl;

	Node<string> newNode("orange");
	list.add_node(newNode, list.find_node("banana"));
	cout << "Actual result:" << endl;
	print(list);
	cout << "------------------------------------------------------------------------------" << endl;
	cout << endl;



	cout << "Finds the mid node of the LinkedList by calling list.find_mid_node(). \nExpected result:" << endl;
	cout << "orange" << endl;
	cout << endl;

	cout << "Actual result:" << endl;
	cout << list.find_mid_node()->get_data() << endl;
	cout << "------------------------------------------------------------------------------" << endl;
	cout << endl;



	cout << "Removes a node that contains the words \"orange\" by calling list.remove_node(\"orange\"). \nExpected result:" << endl;
	cout << "fig \ncherry \nelderberry \nbanana \napple \ndewberry" << endl;
	cout << endl;

	list.remove_node("orange");
	cout << "Actual result:" << endl;
	print(list);
	cout << "------------------------------------------------------------------------------" << endl;
	cout << endl;



	cout << "Removes a node that contains the words \"cherry\" by calling list.remove_node(list.find_node(\"cherry\")) and passing a node as a parameter. \nExpected result:" << endl;
	cout << "fig \nelderberry \nbanana \napple \ndewberry" << endl;
	cout << endl;

	list.remove_node(list.find_node("cherry"));
	cout << "Actual result:" << endl;
	print(list);
	cout << "------------------------------------------------------------------------------" << endl;
	cout << endl;

	/*	cout << "Swap two nodes, where the first node contains the word \"elderberry\" and the second node contains the word \"apple\". \nExpected result:" << endl;
		cout << "fig \napple \nbanana \nelderberry \ndewberry" << endl;
		cout << endl;

		Node<string>* first = list.find_node("elderberry");
		Node<string>* second = list.find_node("apple");

		list.swap_node(first, second);
		cout << "Actual result:" << endl;
		print(list);
		cout << "------------------------------------------------------------------------------" << endl;
		cout << endl;*/

	cout << "Gets the size of the LinkedList by calling list.length(). \nExpected result:" << endl;
	cout << "5" << endl;
	cout << endl;

	cout << "Actual result:" << endl;
	cout << list.length() << endl;
	cout << "------------------------------------------------------------------------------" << endl;
	cout << endl;



	cout << "Gets the head node of the LinkedList by calling list.front() and use get_data() to get the word of that node. \nExpected result:" << endl;
	cout << "fig" << endl;
	cout << endl;

	cout << "Actual result:" << endl;
	cout << list.front()->get_data() << endl;
	cout << "------------------------------------------------------------------------------" << endl;
	cout << endl;



	cout << "Gets the tail node of the LinkedList by calling list.back() and use get_data() to get the word of that node. \nExpected result:" << endl;
	cout << "dewberry" << endl;
	cout << endl;

	cout << "Actual result:" << endl;
	cout << list.back()->get_data() << endl;
	cout << "------------------------------------------------------------------------------" << endl;
	cout << endl;



	cout << "Pops the head node of the LinkedList by calling list.pop_front(). \nExpected result:" << endl;
	cout << "elderberry \nbanana \napple \ndewberry" << endl;
	cout << endl;

	list.pop_front();
	cout << "Actual result:" << endl;
	print(list);
	cout << "------------------------------------------------------------------------------" << endl;
	cout << endl;



	cout << "Pops the tail node of the LinkedList by calling list.pop_back(). \nExpected result:" << endl;
	cout << "elderberry \nbanana \napple" << endl;
	cout << endl;

	list.pop_back();
	cout << "Actual result:" << endl;
	print(list);
	cout << "------------------------------------------------------------------------------" << endl;
	cout << endl;
}