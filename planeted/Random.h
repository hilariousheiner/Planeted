#ifndef PLANETED_RANDOM_H
#define PLANETED_RANDOM_H

#include <algorithm>
#include <array>
#include <functional>
#include <string>

#include "Math.h"
#include "PRNG.h"
#include "Vector2.h"
#include "Vector3.h"

namespace Planeted
{
    namespace Random
    {
        struct FBMParameters
        {
            FBMParameters();

            std::uint32_t NumberOfOctaves;
            float Lacunarity;
            float Persistence;
            float StartFrequency;
            bool Normalize;
        };


        class NoiseParameters
        {
        public:

            NoiseParameters();

            float WhiteNoiseScale;

            void SeedNoise(std::uint32_t seed);
            void SeedNoise(std::string seed);

            std::uint8_t Permute(const std::uint8_t &x) const;
            std::uint8_t Permute(const int &x, const int &y) const;
            std::uint8_t Permute(const int &x, const int &y, const int &z) const;

        //private:
            std::uint32_t seed;
            std::uint64_t seed64;
        private:
            PermutationTable permutationTable;
        };
    }
}
#endif // PLANETED_RANDOM_H
