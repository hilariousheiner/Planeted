#include "FBM.h"

namespace Planeted
{
    FBMParameters::FBMParameters()
    {
        this->NumberOfOctaves = 1;
        this->Lacunarity = 1.0f;
        this->Persistence = 1.0f;
        this->StartFrequency = 1.0f;
        this->Normalize = false;
    }
}
