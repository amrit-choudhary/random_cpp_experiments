#include <vector>
#include <cstdint>
#include <random>

/**
 * Delivery Results
 * No.  Runs    Type    Sub     Ext     Hex     Disp
 * 00   0       DOT     DOT_0    N       0x0    0
 * 01   1       RBW     RBW_0    N       0x1    1
 * 02   2       RBW     RBW_1    N       0x2    2
 * 03   3       RBW     RBW_2    N       0x3    3
 * 04   4       BND     BND_0    N       0x4    4
 * 05   6       BND     BND_1    N       0x5    6
 * 06   0       WCK     WCK_0    N       0x6    W
 * 07   1       WDE     WDE_0    Y       0x7    1+Wd
 * 08   2       WDE     WDE_1    Y       0x8    2+Wd
 * 09   3       WDE     WDE_2    Y       0x9    3+Wd
 * 10   4       WDE     WDE_3    Y       0xA    4+Wd
 * 11   5       WDE     WDE_4    Y       0xB    5+Wd
 * 12   1       NOB     NOB_0    Y       0xC    1+Nb
 *
 *
 *
 * Result Types
 * DOT      10%     0   0x0
 * RBW      30%     1   0x1
 * BND      30%     2   0x4
 * WCK      10%     3   0x6
 * WDE      10%     4   0x7
 * NOB      10%     5   0xC
 *
 * RBW Types
 * 1        40%     0
 * 2        40%     1
 * 3        20%     2
 *
 * Boundary Types
 * 4        70%     0
 * 6        30%     1
 *
 * Wide Types
 * 0        50%     0
 * 1        20%     1
 * 2        10%     2
 * 3        10%     3
 * 4        10%     4
 *
 *
 *
 *
 */

bool FindData(const int runTarget, const int maxLegalBallCount);