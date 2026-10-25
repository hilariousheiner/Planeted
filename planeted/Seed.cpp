#include "Seed.h"

namespace Planeted
{
    Seed::Seed()
        : Seed("Planeted")
    { }

    Seed::Seed(std::uint32_t seed)
        : seed(seed), seed64(FMix64(static_cast<uint64_t>(seed)))
    { }

    Seed::Seed(std::string seed)
        : seed(StringToSeed32(seed)), seed64(StringToSeed64(seed))
    { }

    std::uint32_t Seed::GetSeed()
    {
        return this->seed;
    }
    std::uint64_t Seed::GetSeed64()
    {
        return this->seed64;
    }
}
