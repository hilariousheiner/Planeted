#ifndef PLANETED_PERMUTATIONTABLE_H
#define PLANETED_PERMUTATIONTABLE_H

#include "PRNG.h"
#include <array>
#include <cstdint>

namespace Planeted
{
    using Permutation = std::array<uint8_t, PermutationSize>;

    constexpr int PermutationSize = 256;

    using PermutationTable = std::array<uint8_t, PermutationSize * 2>;

    PermutationTable MakePermutationTable(Permutation &permutation, uint64_t seed);
}
#endif
