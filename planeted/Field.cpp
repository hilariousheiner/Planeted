#include "Field.h"

namespace Planeted
{
    void AFieldGenerator1::SetSeed(std::uint32_t seedValue)
    {
        this->seed = Seed(seedValue);
    }
    void AFieldGenerator1::SetSeed(std::string seedValue)
    {
        this->seed = Seed(seedValue);
    }

    void AFieldGenerator2::SetSeed(std::uint32_t seedValue)
    {
        this->seed = Seed(seedValue);
    }
    void AFieldGenerator2::SetSeed(std::string seedValue)
    {
        this->seed = Seed(seedValue);
    }

    void AFieldGenerator3::SetSeed(std::uint32_t seedValue)
    {
        this->seed = Seed(seedValue);
    }
    void AFieldGenerator3::SetSeed(std::string seedValue)
    {
        this->seed = Seed(seedValue);
    }
}
