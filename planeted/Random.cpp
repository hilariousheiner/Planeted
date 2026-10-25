#include "Random.h"

#include <cmath> //for std::abs and std::pow

namespace Planeted
{
    namespace Random
    {
        static Permutation permutation =
        {
            8  , 170, 242, 67 , 248, 216, 115, 247, 164, 133, 195, 73 , 45 , 209, 13 , 53 ,
            9  , 131, 102, 214, 153, 254, 224, 63 , 244, 51 , 7  , 172, 106, 137, 95 , 201,
            41 , 71 , 166, 186, 83 , 197, 96 , 89 , 175, 226, 129, 34 , 80 , 97 , 93 , 12 ,
            84 , 70 , 152, 22 , 134, 125, 210, 135, 139, 49 , 100, 105, 109, 165, 117, 228,
            37 , 107, 11 , 24 , 128, 239, 86 , 88 , 108, 28 , 120, 76 , 98 , 19 , 118, 221,
            1  , 218, 82 , 179, 64 , 94 , 44 , 141, 149, 168, 99 , 187, 46 , 123, 243, 167,
            50 , 143, 85 , 193, 25 , 62 , 56 , 203, 200, 198, 26 , 119, 65 , 146, 246, 145,
            191, 15 , 91 , 233, 206, 176, 148, 48 , 78 , 27 , 35 , 101, 184, 87 , 207, 180,
            177, 23 , 81 , 219, 124, 55 , 250, 42 , 196, 59 , 5  , 161, 38 , 114, 230, 150,
            156, 10 , 240, 112, 31 , 162, 241, 213, 160, 238, 69 , 18 , 32 , 144, 151, 116,
            223, 234, 211, 154, 140, 127, 6  , 194, 122, 79 , 113, 75 , 217, 192, 163, 58 ,
            14 , 92 , 251, 190, 54 , 188, 227, 77 , 103, 181, 3  , 132, 208, 155, 253, 121,
            255, 60 , 245, 202, 157, 130, 52 , 36 , 173, 169, 74 , 29 , 39 , 4  , 17 , 147,
            47 , 61 , 252, 204, 159, 232, 225, 229, 57 , 43 , 237, 142, 183, 104, 72 , 236,
            2  , 189, 66 , 111, 30 , 158, 215, 126, 138, 220, 231, 249, 16 , 20 , 0  , 33 ,
            212, 182, 136, 185, 110, 40 , 235, 21 , 222, 178, 174, 205, 68 , 90 , 171, 199
        };

        NoiseParameters::NoiseParameters()
        {
            this->SeedNoise("Planeted");
        }

        void NoiseParameters::SeedNoise(std::uint32_t seed)
        {
            this->seed = seed;
            this->seed64 = FMix64(static_cast<uint64_t>(seed));

            this->permutationTable = MakePermutationTable(Random::permutation, this->seed64);
        }
        void NoiseParameters::SeedNoise(std::string seed)
        {
            this->seed = StringToSeed32(seed);
            this->seed64 = StringToSeed64(seed);

            this->permutationTable = MakePermutationTable(Random::permutation, this->seed64);
        }

        std::uint8_t NoiseParameters::Permute(const std::uint8_t &x) const
        {
            return this->permutationTable[x];
        }
        std::uint8_t NoiseParameters::Permute(const int &x, const int &y) const
        {
            return this->permutationTable[this->permutationTable[x] + y];
        }
        std::uint8_t NoiseParameters::Permute(const int &x, const int &y, const int &z) const
        {
            return this->permutationTable[this->permutationTable[this->permutationTable[x] + y] + z];
        }
    }
}
