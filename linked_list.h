#pragma once

#include <stdint.h>

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

struct UnionTest
{
    int32_t i;
    float f;
    union
    {
        int32_t iu;
        bool b;
        int64_t iul;
    };
};