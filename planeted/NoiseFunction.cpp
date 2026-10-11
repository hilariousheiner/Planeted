#include "NoiseFunction.h"

namespace Planeted
{
    NoiseFunction::NoiseFunction() { }

    float NoiseFunction::Noise1D(const float &p) const
    {
        return Random::FBM1D(p, this->fbmParams, this->noiseParams, Random::GetNoiseFunction1D(this->noiseType, this->noiseStyle));
    }
    float NoiseFunction::Noise2D(const Vector2 &p) const
    {
        return Random::FBM2D(p, this->fbmParams, this->noiseParams, Random::GetNoiseFunction2D(this->noiseType, this->noiseStyle));
    }
    float NoiseFunction::Noise3D(const Vector3 &p) const
    {
        return Random::FBM3D(p, this->fbmParams, this->noiseParams, Random::GetNoiseFunction3D(this->noiseType, this->noiseStyle));
    }

    void NoiseFunction::SetNumberOfOctaves(std::uint32_t numberOfOctaves)
    {
        this->fbmParams.NumberOfOctaves = numberOfOctaves;
    }

    void NoiseFunction::SetStartFrequency(float startFrequency)
    {
        this->fbmParams.StartFrequency = startFrequency;
    }

    void NoiseFunction::SetLacunarity(float lacunarity)
    {
        this->fbmParams.Lacunarity = lacunarity;
    }

    void NoiseFunction::SetPersistence(float persistence)
    {
        this->fbmParams.Persistence = persistence;
    }

    void NoiseFunction::SetNormalizeFBM(bool normalize)
    {
        this->fbmParams.Normalize = normalize;
    }

    void NoiseFunction::SetExponent(float exponent)
    {
        this->fbmParams.Exponent = exponent;
    }

    void NoiseFunction::SetWhiteNoiseScale(float scale)
    {
        this->noiseParams.WhiteNoiseScale = scale;
    }
}
