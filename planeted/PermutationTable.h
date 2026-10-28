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

        PermutationTable() = default;
        PermutationTable(Permutation &permutation, uint64_t seed);

        std::uint8_t Permute(const std::uint8_t &x) const;
        std::uint8_t Permute(const int &x, const int &y) const;
        std::uint8_t Permute(const int &x, const int &y, const int &z) const;

        static std::uint8_t ToGrid(const int &x);

    private:
        using internalTable = std::array<uint8_t, PermutationSize * 2>;

        static internalTable makePermutationTable(Permutation &permutation, uint64_t seed);
        internalTable table;
    };
}
#endif
