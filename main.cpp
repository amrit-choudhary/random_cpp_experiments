#include <iostream>
#include <vector>
#include <string>
#include "linked_list.h"
#include <chrono>
#include <ctime>

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

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    while(l != nullptr && counter < 10000000)
    {
        // std::cout << l->value << ", ";
        sum += l->value;
        l = l->next;
        ++counter;
    }

    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";

    std::cout << sum << std::endl;
    std::cout << "\nEnd\n";

    char c;
    std::cin >> c;
}
