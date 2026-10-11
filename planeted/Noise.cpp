#include "Noise.h"
#include "PRNG.h"

namespace Planeted
{
    float ANoise::Eval1D(const float &p) const
    {
        float result = 0.0f;

        float frequency = this->fbmParams.StartFrequency;
        float amplitude = 1.0f;

        float t = 0.0f;

        for(std::uint32_t i = 0; i < this->fbmParams.NumberOfOctaves; ++i)
        {
            result += amplitude*this->noise1D(p*frequency);

            t += amplitude;
            frequency *= this->fbmParams.Lacunarity;
            amplitude *= this->fbmParams.Persistence;
        }

        if(this->fbmParams.Normalize)
        {
            result = result / t;
        }
    }

    float ANoise::Eval2D(const Vector2 &p) const
    {
        return 0;
    }

    float ANoise::Eval3D(const Vector3 &p) const
    {
        return 0;
    }
}
