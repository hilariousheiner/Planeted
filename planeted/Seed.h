#ifndef PLANETED_SEED_H
#define PLANETED_SEED_H

#include "PRNG.h"

namespace Planeted
{
    class Seed
    {
    public:
        Seed();
        Seed(std::uint32_t seed);
        Seed(std::string seed);

        std::uint32_t GetSeed() const;
        std::uint64_t GetSeed64() const;

    private:
        std::uint32_t seed;
        std::uint64_t seed64;
    };
}
#endif
