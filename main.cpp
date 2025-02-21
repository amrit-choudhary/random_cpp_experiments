#include <iostream>
#include <vector>
#include <string>
#include "linked_list.h"

int main()
{
    TestFn();
    LinkedList list1 = LinkedList(1);
    LinkedList list2 = LinkedList(2);
    list1.next = &list2;
    LinkedList list3 = LinkedList(3);
    list2.next = &list3;
    LinkedList list4 = LinkedList(4);
    list3.next = &list4;

    list4.next = &list1;

    LinkedList *l = &list1;
    int counter = 0;
    int sum = 0;

    while(l != nullptr && counter < 10000000)
    {
        // std::cout << l->value << ", ";
        sum += l->value;
        l = l->next;
        ++counter;
    }

    std::cout << sum << std::endl;
    std::cout << "\nEnd\n";

    char c;
    std::cin >> c;
}
