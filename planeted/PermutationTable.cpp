
#include "PermutationTable.h"

namespace Planeted
{
    PermutationTable::PermutationTable(Permutation &permutation, uint64_t seed)
    {
        this->table = PermutationTable::makePermutationTable(permutation, seed);
    }

    std::uint8_t PermutationTable::Permute(const std::uint8_t &x) const
    {
        return this->table[x];
    }
    std::uint8_t PermutationTable::Permute(const int &x, const int &y) const
    {
        return this->table[this->table[x] + y];
    }
    std::uint8_t PermutationTable::Permute(const int &x, const int &y, const int &z) const
    {
        return this->table[this->table[this->table[x] + y] + z];
    }

    std::uint8_t PermutationTable::Permute(const internalTable &table, const std::uint8_t &x) //const;
    {
        return table[x];
    }
    std::uint8_t PermutationTable::Permute(const internalTable &table, const int &x, const int &y) //const;
    {
        return table[table[x] + y];
    }
    std::uint8_t PermutationTable::Permute(const internalTable &table, const int &x, const int &y, const int &z) //const;
    {
        return table[table[table[x] + y] + z];
    }


    std::uint8_t PermutationTable::ToGrid(const int &x)
    {
        return static_cast<std::uint8_t>(x & (PermutationTable::PermutationSize - 1));
    }


    PermutationTable::internalTable PermutationTable::makePermutationTable(Permutation &permutation, uint64_t seed)
    {
        PermutationTable::internalTable result;

        // copy the permutation into the first half of the table:
        for (int i = 0; i < PermutationSize; ++i)
        {
            result[i] = permutation[i];
        }

        // shuffle the first half of the table
        // using a Fisher-Yates shuffle with SplitMix64:
        uint64_t state = seed;

        for (int i = PermutationSize-1; i > 0; --i)
        {
            int j = static_cast<int>(SplitMix64(state) % (i + 1));
            std::swap(result[i], result[j]);
        }

        // duplicate the shuffled permutation into the second half of the table:
        for (int i = 0; i < PermutationSize; ++i)
        {
            result[i + PermutationSize] = result[i];
        }

        // done.
        return result;
    }
}
