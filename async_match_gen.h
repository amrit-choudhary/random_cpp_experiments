#pragma once

#include <cstdint>

/**
 * Delivery Results
 * ID   Runs    Type    SubType Extra   HexID   Disp
 * 00   0       DOT     DOT_0    N      0x0    0
 * 01   1       RBW     RBW_0    N      0x1    1
 * 02   2       RBW     RBW_1    N      0x2    2
 * 03   3       RBW     RBW_2    N      0x3    3
 * 04   4       BND     BND_0    N      0x4    4
 * 05   6       BND     BND_1    N      0x5    6
 * 06   0       WCK     WCK_0    N      0x6    W
 * 07   1       WDE     WDE_0    Y      0x7    1+Wd
 * 08   2       WDE     WDE_1    Y      0x8    2+Wd
 * 09   3       WDE     WDE_2    Y      0x9    3+Wd
 * 10   4       WDE     WDE_3    Y      0xA    4+Wd
 * 11   5       WDE     WDE_4    Y      0xB    5+Wd
 * 12   1       NOB     NOB_0    Y      0xC    1+Nb
 *
 *
 * Delivery Result Types (variation = medium, Expected runs per ball = 1.54)
 * DOT      10%     0   0x0
 * RBW      30%     1   0x1
 * BND      30%     2   0x4
 * WCK      10%     3   0x6
 * WDE      10%     4   0x7
 * NOB      10%     5   0xC
 *
 *
 * Result Types (No-Wide, No-Noball)
 * DOT      30%     0   0x0
 * RBW      30%     1   0x1
 * BND      30%     2   0x4
 * WCK      10%     3   0x6
 * WDE      00%     4   0x7
 * NOB      00%     5   0xC
 *
 *
 * RBW Sub Types
 * Runs     Chance  ID
 * 1        40%     0x0
 * 2        40%     0x1
 * 3        20%     0x2
 *
 *
 * Boundary Types
 * Runs     Chance  ID
 * 4        70%     0x0
 * 6        30%     0x1
 *
 *
 * Wide Types
 * Runs     Chance  ID
 * 0        50%     0x0
 * 1        20%     0x1
 * 2        10%     0x2
 * 3        10%     0x3
 * 4        10%     0x4
 *
 */


namespace AsyncMatchGen
{
    /**
     * This will retry the FindData() function some number of times.
     * If a valid solution can't be found within max tries, it will decrease runTarget by 1 and try again. 
     */
    bool FindDataGuaranteed(const int runTarget, const int maxLegalBallCount, uint8_t* result_array);
    std::string GetDisplayName(const uint8_t index);
    bool CheckWicket(const uint8_t code);
    uint8_t GetRuns(const uint8_t code);
    bool CheckFour(const uint8_t code);
    bool CheckSix(const uint8_t code);
}
