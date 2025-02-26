#include <iostream>
#include <vector>
#include <string>
#include "linked_list.h"
#include <chrono>
#include <ctime>
#include "async_match_gen.h"

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    std::random_device rdev1;
    std::mt19937 rgen1(rdev1());
    std::uniform_int_distribution<uint8_t> idist1(0, 9);
    uint8_t result_type_lut1[10] = {0, 1, 1, 1, 2, 2, 2, 3, 4, 5};

    uint32_t result[6] = {0, 0, 0, 0, 0, 0};

    for (int i = 0; i < 1000; i++)
    {
        if (FindData(36, 11))
        {
            std::cout << "Count: " << i << std::endl;
            break;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_microseconds = end - start;

    std::cout << "elapsed time: " << elapsed_microseconds.count() / 1000 << " micros\n";

    std::cout << "" << std::endl;
    std::cout << "\nEnd\n";

    char c;
    std::cin >> c;
}
