#include "NoiseFunction.h"

namespace Planeted
{
    NoiseFunction::NoiseFunction() { }

    std::unique_ptr<NoiseFunction> NoiseFunction::Clone() const
    {
        return std::make_unique<NoiseFunction>(*this);
    }

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

    void NoiseFunction::SeedNoise(std::uint32_t seed)
    {
        this->noiseParams.SeedNoise(seed);
    }
    void NoiseFunction::SeedNoise(std::string seed)
    {
        this->noiseParams.SeedNoise(seed);
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

    void NoiseFunction::SetWhiteNoiseScale(float scale)
    {
        this->noiseParams.WhiteNoiseScale = scale;
    }
}
