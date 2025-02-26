#include <iostream>
#include <string>
#include "async_match_gen.h"

static std::string result_code_lut[13] =
    {
        "DOT_0",
        "RBW_0", "RBW_1", "RBW_2",
        "BND_0", "BND_1",
        "WCK_0",
        "WDE_0", "WDE_1", "WDE_2", "WDE_3", "WDE_4",
        "NOB_0"};
static std::string result_display_lut[13] =
    {
        "0",
        "1", "2", "3",
        "4", "6",
        "W",
        "1+Wd", "2+Wd", "3+Wd", "4+Wd", "5+Wd",
        "1+Nb"};
static uint8_t result_runs_lut[13] =
    {
        0,
        1, 2, 3,
        4, 6,
        0,
        1, 2, 3, 4, 5,
        1};
static uint8_t result_type_lut[10] = {0, 1, 1, 1, 2, 2, 2, 3, 4, 5};
static uint8_t rbw_type_lut[10] = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2};
static uint8_t boundary_type_lut[10] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1};
static uint8_t wide_type_lut[10] = {0, 0, 0, 0, 0, 1, 1, 2, 3, 4};

static std::random_device rdev;
static std::mt19937 rgen(rdev());
static std::uniform_int_distribution<uint8_t> idist(0, 9);

uint8_t RndFromLUT(uint8_t *lut)
{
    uint8_t rndIndex = idist(rgen);
    uint8_t result = lut[rndIndex];
    return result;
}

uint8_t RndFromLUT()
{
    return RndFromLUT(result_type_lut);
}

bool FindData(const int runTarget = 36, const int maxLegalBallCount = 11)
{
    uint8_t result[22] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t legalBallCount = 0;
    uint8_t ballCount = 0;

    while (legalBallCount <= maxLegalBallCount)
    {
        // Find result
        uint8_t res = RndFromLUT(result_type_lut);
        switch (res)
        {
        case 0: // Dot
            result[ballCount] = 0x0;
            legalBallCount++;
            ballCount++;
            break;

        case 1: // RBW
            result[ballCount] = 0x1 + RndFromLUT(rbw_type_lut);
            legalBallCount++;
            ballCount++;
            break;

        case 2: // BND
            result[ballCount] = 0x4 + RndFromLUT(boundary_type_lut);
            legalBallCount++;
            ballCount++;
            break;

        case 3: // WCK
            result[ballCount] = 0x6;
            legalBallCount++;
            ballCount++;
            break;

        case 4: // WDE
            result[ballCount] = 0x7 + RndFromLUT(wide_type_lut);
            ballCount++;
            break;

        case 5: // NOB
            result[ballCount] = 0xC;
            ballCount++;
            break;

        default:
            break;
        }
    }

    int score = 0;
    for (int i = 0; i < ballCount; i++)
    {
        // std::cout << result_display_lut[result[i]] << "\t";
        score += result_runs_lut[result[i]];
    }
    
    return (score == runTarget);
}