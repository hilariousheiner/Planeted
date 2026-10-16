#ifndef PLANETED_NOISEFUNCTION_H
#define PLANETED_NOISEFUNCTION_H

#include <memory>

#include "Random.h"

namespace Planeted
{
    class NoiseFunction
    {
    public:
        NoiseFunction();
        std::unique_ptr<NoiseFunction> Clone() const;

        float Noise1D(const float &p) const;
        float Noise2D(const Vector2 &p) const;
        float Noise3D(const Vector3 &p) const;

        void SeedNoise(std::uint32_t seed);
        void SeedNoise(std::string seed);

        void SetNumberOfOctaves(std::uint32_t numberOfOctaves);
        void SetStartFrequency(float startFrequency);
        void SetLacunarity(float lacunarity);
        void SetPersistence(float persistence);
        void SetNormalizeFBM(bool normalize);
        void SetExponent(float exponent);

        void SetWhiteNoiseScale(float scale);

        Random::NoiseTypeEnum noiseType;
        Random::NoiseStyleEnum noiseStyle;

        Random::FBMParameters fbmParams;
        Random::NoiseParameters noiseParams;
    };
}
#endif
