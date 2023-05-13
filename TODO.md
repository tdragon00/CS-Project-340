# Roadmap

## Stage 1

In this stage, we want to focus on converting the basic linked list struct
to template classes, and do additional refactoring on the code to have less
'smell' on the code

### Things to do
- [x] convert structs to classes
- [x] convert classes to templates
- [ ] refactor code
  - [ ] make all data fields to getters and setters
  - [ ] add utility functions for the list
    - `size()` - get the size of the list
    - `back()` - get the end of the list (NOTE: head is already given due to data field)
    - `pop_front()` - pop the front node of the list
    - `pop_back()` - pop the back node of the list

### Possible things to include
- create an iterator for list

## Interlude

We'll probably want to create a testbench or do unit testing in each functions
to make sure everything is working well

### Things to do
- [ ] create unit tests
   - have some values to compare the output of the list (i.e. is x == y? etc)
   - think of fail cases that might cause the list to bug out and fix them

## Stage 2 - Mini Program and Skip List
[Skip List](https://www.geeksforgeeks.org/skip-list/#)

In this stage, we want to convert the linked list to a skip list.
The skip list will always insert nodes in a sorted order, thus not
needing any sort of sorts. In addition to the linked list, we want
to implement a mini program in parallel with the skip list. It could
be any sort of program (a minigame, a CRUD, etc.)

To better manage this stage, we'll split it to separate stage that
can work in parallel

### Stage 2a - Skip List
- [x] create layers of pointers that will point to locations in the list
   - This is a modified Node object with an up and down datafield
- [x] determine the height of the vector and how it will point to a specific
area of the list
   - possibly do the coin flip method to determine the height
     - more info [here](https://www.geeksforgeeks.org/skip-list-set-2-insertion/)
- [ ] add insertion and deletion functions
   - this will replace the old insertion and deletions functions
   - insertion will insert in sorted order (i.e 50 will be inserted between 49 and 51)
   - deletion, will delete the node, and relink the prev and next node
- [x] search function
   - could be a binary search, since the list will always be sorted

#### Possible things to include
- Auto update list, if a node updates (i.e. if Node 1's content becomes lower, then it will
move down the list etc.)

### Stage 2b- Mini Program
-- TODO --
