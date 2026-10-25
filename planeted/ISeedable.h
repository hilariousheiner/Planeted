#ifndef PLANETED_ISEEDABLE_H
#define PLANETED_ISEEDABLE_H

#include <cstdint>
#include <string>

namespace Planeted
{
    class ISeedable
    {
    public:
        virtual ~ISeedable() = default;

        virtual void SetSeed(std::uint32_t seed) = 0;
        virtual void SetSeed(std::string seed) = 0;
    };
}
#endif
