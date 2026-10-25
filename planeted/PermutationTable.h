#ifndef PLANETED_PERMUTATIONTABLE_H
#define PLANETED_PERMUTATIONTABLE_H

#include "PRNG.h"
#include <array>
#include <cstdint>

namespace Planeted
{
    class PermutationTable
    {
    public:
        static constexpr int PermutationSize = 256;

        using Permutation = std::array<uint8_t, PermutationSize>;

        using InternalTable = std::array<uint8_t, PermutationSize * 2>;

        static InternalTable MakePermutationTable(Permutation &permutation, uint64_t seed);
    };
}
#endif
