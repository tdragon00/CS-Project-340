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

#include <string>   // for string
#include <iostream> //  for stdcout 
#include <conio.h> // for getch
#include <iostream> // for files
#include <time.h>
#include <fstream>
#include "list.h"
#include "list.cpp"
#include "skip_list.h"
#include "skip_list.cpp"

using namespace std;

/*
NOTE: We don't really need these right now,
void linear_sort(LinkedList* &list);
LinkedList* merge_sort(LinkedList* &list);
LinkedList* merge_dicts(LinkedList* list_1, LinkedList* list_2);
void add_to_dict(LinkedList* &list, Node* node);
void sort_dicts(LinkedList* &list, Node* node_1, Node* node_2);

*/

template <typename T>
void print(LinkedList<T> &list);
void print_menu();
char print_typemenu();
int intprompt();
void print_skip_menu();
string const fname1 = "strings.txt";
string const fname2 = "int.txt";

//this is our main driver function it will display a menu with several options to use 
//different lists

int main()
{    
    //since c++ is statically typed things here are about to get real ugly
    //creating our lists for int and string
    LinkedList<int> intlist;
    LinkedList<string> stringlist;
    SkipList<string> stringskiplist;
    srand(time(nullptr));
   
    
    //type of the list we have
    char type = print_typemenu();
    //variable to store the choice of the menu this is not the same as above
    char choice = 's';
    //container to hold inputs since strings can't really be fed wrong info
    string target;
    int holder;
    //main loop

    //containers for searches.
    Node<int> *intnodepointer;
    Node<string> *stringnodepointer;
     SkipNode<string> *container = nullptr;

     ifstream myfile;
    while (choice != 'q')
    {
        //printing menu and getting the users choice 
         if(type == '2' || type == '1' ) 
        {
            print_menu();
        }
        else
        {
        print_skip_menu();
        }
         
           //clearing the buffer
         cin.get();
        choice = getchar();
      
      //switch case to determine what data we are using 
        switch (type)
        {
            //int case
        case '1':
            //switch case int
            //this switch statement is used to determine what actions are going to be taken on the list
            switch (choice)
            {
            case '1':
                //insert at front
                intlist.push_front(intprompt());
                break;
            case '2':
                //insert at back
                intlist.push_back(intprompt());
                break;
            case '3':
                //search          
                intnodepointer = intlist.find_node(intprompt());
                if (intnodepointer == nullptr)
                {
                    cout << "could not find your value" << endl;
                }
                else
                    cout << "we found your value "<< intnodepointer->get_data() << endl;
                break;
            case '4':
                //print
                print(intlist);
                break;
            case '5':
                //pop back
                intlist.pop_back();
                break;
            case '6':
                //delete
                intlist.pop_front();
                break;

            case'7':

                cout << "case 7" << endl;
                myfile.open(fname2);

                if (myfile.is_open())
                { // always check whether the file is open
                    //cout << "file found" << endl;;


                    while (!myfile.eof())
                    {
                       // cout << "help";
                        myfile >> holder;
                        intlist.push_back(holder);
                        cout << holder;

                    }
                    myfile.close();
                }else
                {
                    cout << "file not found" << endl;
                }

            
            break;

            default:
                break;
            }
            break;
            //string case
        case '2':
            //switch case string
            //this switch statement is used to determine what actions are going to be taken on the list
            switch (choice)
            {
            case '1':
                //insert at front
                cin >> target;
                stringlist.push_front(target);
                break;
            case '2':
                //insert at back
                cin >> target;
                stringlist.push_back(target);
                break;
            case '3':
                cout<<"Enter what you want to find"<<endl;
                cin>>target;
                         stringnodepointer = stringlist.find_node(target);
                if( stringnodepointer == nullptr)
                {
                    cout<<"could not find your value"<<endl;
                }
                else 
                cout<<"we found your value "+ stringnodepointer->get_data()<<endl;
                
                break;
            case '4':
                print(stringlist);
                //print
                break;
            case '5':
            //pop back
            stringlist.pop_back();
            break;

            case '6':
            //delete
             stringlist.pop_front();
            break;

            
            case '7':
            myfile.open(fname1);
            if (myfile.is_open())
            { // always check whether the file is open
                while (!myfile.eof())
                {
                    myfile >> target;
                    stringlist.push_back(target);
                }
            }
            myfile.close();
            break;


            default:
                break;
            }
            break;
            //char case
        case '3':
        switch (choice)
            {
            case '1':
                //insert  front
                cin >> target;
                stringskiplist.insert(target);
                break;
            case '2':
                //remove
                cin >> target;
                stringskiplist.remove_node(target);
                break;
            case '3':
                //search
                cin>>target;
                container = stringskiplist.search(target);
                if(container !=nullptr )
                {
                    cout<<"your word was found "<<container->get_data()<<endl;
                }else
                cout<<"your word was not found"<<endl;
                container = nullptr; 
                //cout << "coming soon" << endl;
                break;
            case '4':
                stringskiplist.pretty_print();
                //print
                break;

            case '5':
                myfile.open(fname1);
                if (myfile.is_open())
                { // always check whether the file is open
                    while (!myfile.eof())
                    {
                        myfile >> target;
                        stringskiplist.insert(target);
                    }
                }
                myfile.close();
            default:
                break;
            }
            break;
        default:
            break;
        }


    }
    /*
    LinkedList<string> test = LinkedList<string>();
    test.push_front("hi");
    test.push_front("ww");
    Node<string>* head = test.front();
    cout << head->get_data() << endl;
    Node<string>* test_node = test.binary_find_node("hi", head, test.length());

    if (test_node != nullptr)
    {
        cout << test_node->get_data() << endl;

        test_node->set_data("wassup");
    }

    cout << "Hello dlrow" << endl;

    print(test);

    */
}
//simple print function 
template <typename T>
void print(LinkedList<T> &list) 
{
    Node<T>* iter = list.front();
    for (int i = 0; i < list.length(); i++) 
    {
        cout << iter->get_data() << endl;
        iter = iter->get_next();
    }
}
//simple menu for displaying the options
void print_menu()
{
    cout << "__________________________________________" << endl;
    cout << " 1 Insert at the front" << endl;
    cout << " 2 Insert at the back" << endl;
    cout << " 3 Search" << endl;
    cout << " 4 print" << endl;
    cout << " 5 pop back" << endl;
    cout << " 6 pop front" << endl;
    cout << "7 Load a list " << endl;
    cout << "q quit the program" << endl;
    cout << "__________________________________________" << endl;
}
void print_skip_menu()
{
    cout << "__________________________________________" << endl;
    cout << " 1 Insert " << endl;
    cout << " 2 Delete " << endl;
    cout << " 3 Search" << endl;
    cout << " 4 print" << endl;
      cout << "5 Load a list " << endl;
    
    //cout << " 6 change the list type" << endl;
    cout << "q quit the program" << endl;
    cout << "__________________________________________" << endl;

}


//helper function to determine if the string only contains digits
bool isdigits(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}
//this prompts the user to enter an int it will continue until we only get digits.
int intprompt() 
{
    string x;
while(1)
{
    cout << "please enter an int " << endl;
    cin >> x;
    if (isdigits(x)) 
    {
        return  stoi(x);
    }
}
}
//this prints the type menu this is only used once.
char print_typemenu() 
{
    char type;
    while (1)
    {
        cout << "What data type do you want this list to be " << endl;
        cout << "1: int" << endl;
        cout << "2: string" << endl;
        cout << "3:  string skiplist"<<endl;
        //cout << "c: char" << endl;
        cin.get(type);
        if (type == '1' || type == '2' || type == '3')
        {
            return type;
            break;
        }
        cout << "Invalid input try again " << endl;
    }
}
/*
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
*/