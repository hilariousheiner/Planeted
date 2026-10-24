#ifndef PLANETED_FBM_H
#define PLANETED_FBM_H

#include <cstdint>
#include <string>

namespace Planeted
{
    struct FBMParameters
    {
        FBMParameters();

        std::uint32_t NumberOfOctaves;
        float Lacunarity;
        float Persistence;
        float StartFrequency;
        bool Normalize;
    };
}
#endif
