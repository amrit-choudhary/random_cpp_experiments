#include <string>
#include <random>
#include "async_match_gen.h"

// Reason for using anonymous namespace instead of static for these variables.
// Refer: https://stackoverflow.com/questions/154469/why-should-you-prefer-unnamed-namespaces-over-static-functions
// Result: lifetime = static, scope = this file only, linkage = internal.
namespace
{
    std::string code_lut[13] =
    {
        "DOT_0",
        "RBW_0", "RBW_1", "RBW_2",
        "BND_0", "BND_1",
        "WCK_0",
        "WDE_0", "WDE_1", "WDE_2", "WDE_3", "WDE_4",
        "NOB_0"
    };
    std::string display_lut[13] =
    {
        "0",
        "1", "2", "3",
        "4", "6",
        "W",
        "1+Wd", "2+Wd", "3+Wd", "4+Wd", "5+Wd",
        "1+Nb"
    };
    uint8_t runs_lut[13] =
    {
        0,
        1, 2, 3,
        4, 6,
        0,
        1, 2, 3, 4, 5,
        1
    };
    bool check_wicket_lut[13] =
    {
        false,
        false, false, false,
        false, false,
        true,
        false, false, false, false, false,
        false
    };
    bool check_four_lut[13] =
    {
        false,
        false, false, false,
        true, false,
        false,
        false, false, false, false, false,
        false
    };
    bool check_six_lut[13] =
    {
        false,
        false, false, false,
        false, true,
        false,
        false, false, false, false, false,
        false
    };
    bool check_wide_lut[13] =
    {
        false,
        false, false, false,
        false, false,
        false,
        true, true, true, true, true,
        false
    };
    // delivery result chance variations.
    // Refer to this doc for % and expected value calc: Async Bowling Gen on Google Sheets.
    constexpr uint8_t variation_count = 5;
    uint8_t low_result_lut[10] = {0, 0, 0, 0, 0, 1, 1, 1, 2, 3}; // Expected run per ball = 1.00
    uint8_t medium_result_lut[10] = {0, 0, 1, 1, 1, 1, 1, 1, 2, 3}; // Expected run per ball = 1.54
    uint8_t high_result_lut[10] = {0, 0, 1, 1, 1, 2, 2, 2, 2, 3}; // Expected run per ball = 2.38
    uint8_t pro_result_lut[10] = {0, 1, 1, 2, 2, 2, 2, 2, 2, 3}; // Expected run per ball = 3.12
    uint8_t max_result_lut[10] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}; // Expected run per ball = 4.60

    uint8_t* result_luts[variation_count] = {
        low_result_lut, medium_result_lut, high_result_lut, pro_result_lut, max_result_lut
    };

    uint8_t rbw_type_lut[10] = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2};
    uint8_t boundary_type_lut[10] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1};
    uint8_t wide_type_lut[10] = {0, 0, 0, 0, 0, 1, 1, 2, 3, 4};

    std::random_device rdev;
    std::mt19937 rgen(rdev());
    std::uniform_int_distribution<unsigned short> idist(0, 9);

    uint8_t RndFromLUT(uint8_t* lut)
    {
        uint8_t rndIndex = static_cast<uint8_t>(idist(rgen));
        uint8_t result = lut[rndIndex];
        return result;
    }

    bool FindData(const int runTarget = 36, const int maxLegalBallCount = 11, uint8_t* result_array = nullptr)
    {
        uint8_t result[22] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        uint8_t legalBallCount = 0;
        uint8_t ballCount = 0;

        // Picking correct result lut based on target score, out of 5 available lut variations.
        uint8_t result_lut_index = runTarget / maxLegalBallCount;
        if (result_lut_index > variation_count - 1) result_lut_index = variation_count - 1;
        uint8_t* result_lut = result_luts[result_lut_index];

        while (legalBallCount <= maxLegalBallCount)
        {
            // Find delivery result
            uint8_t res = RndFromLUT(result_lut);
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

        ballCount--; // ball count should have exceeded by 1 on last loop.
        int score = 0;
        for (int i = 0; i < ballCount; i++)
        {
            score += runs_lut[result[i]];
        }
        if (score == runTarget)
        {
            std::memcpy(result_array, result, sizeof(result));
            return true;
        }
        return false;
    }
}

namespace AsyncMatchGen
{
    std::string GetDisplayName(const uint8_t code)
    {
        return display_lut[code];
    }

    bool CheckWicket(const uint8_t code)
    {
        return check_wicket_lut[code];
    }

    uint8_t GetRuns(const uint8_t code)
    {
        return runs_lut[code];
    }

    bool CheckFour(const uint8_t code)
    {
        return check_four_lut[code];
    }

    bool CheckSix(const uint8_t code)
    {
        return check_six_lut[code];
    }

    bool FindDataGuaranteed(const int runTarget, const int maxLegalBallCount, uint8_t* result_array)
    {
        constexpr uint8_t max_tries = 20;
        constexpr uint8_t max_tries_per_target = 100;
        int adjustedRunTarget = runTarget;
        bool solutionFound = false;

        for (int n = 0; n < max_tries; n++)
        {
            for (int i = 0; i < max_tries_per_target; i++)
            {
                if (FindData(adjustedRunTarget, maxLegalBallCount, result_array))
                {
                    solutionFound = true;
                    break;
                }
            }
            if (solutionFound)
            {
                return true;
            }
            adjustedRunTarget--;
        }

        return false; // should never reach here.
    }
}
