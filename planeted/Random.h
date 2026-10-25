#ifndef PLANETED_RANDOM_H
#define PLANETED_RANDOM_H

#include <algorithm>
#include <array>
#include <functional>
#include <string>

#include "Math.h"
#include "PRNG.h"
#include "PermutationTable.h"
#include "Vector2.h"
#include "Vector3.h"

namespace Planeted
{
    namespace Random
    {
        class NoiseParameters
        {
        public:

            NoiseParameters();

            void SetSeed(std::uint32_t seed);
            void SetSeed(std::string seed);

            std::uint8_t Permute(const std::uint8_t &x) const;
            std::uint8_t Permute(const int &x, const int &y) const;
            std::uint8_t Permute(const int &x, const int &y, const int &z) const;

            std::uint32_t seed;
            std::uint64_t seed64;
        private:
            PermutationTable permutationTable;
        };
    }
}
#endif // PLANETED_RANDOM_H
