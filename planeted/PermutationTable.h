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

        static std::uint8_t ToGrid(const int &x);

        static std::uint8_t Permute(const InternalTable &table, const std::uint8_t &x); //const;
        static std::uint8_t Permute(const InternalTable &table, const int &x, const int &y); //const;
        static std::uint8_t Permute(const InternalTable &table, const int &x, const int &y, const int &z); //const;
    };
}
#endif
