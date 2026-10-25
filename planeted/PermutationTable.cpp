
#include "PermutationTable.h"

namespace Planeted
{
    PermutationTable MakePermutationTable(Permutation &permutation, uint64_t seed)
    {
        PermutationTable result;

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
