#include "linked_list.h"
#include <iostream>

void TestFn(){
    std::cout << "Hello from linked list.\n";
}

LinkedList::LinkedList()
{
    value = 0;
}

LinkedList::LinkedList(int val)
{
    value = val;
    next = nullptr;
}

LinkedList::~LinkedList()
{
    std::cout << "Destructor of Linked List";
}
