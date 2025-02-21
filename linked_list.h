#pragma once

void TestFn();

class LinkedList
{
public:
    int value;
    LinkedList *next;

    LinkedList();
    LinkedList(int val);
    ~LinkedList();

};