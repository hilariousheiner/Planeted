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

        for(std::uint32_t i = 0; i < this->fbmParams.NumberOfOctaves; i++)
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
        return std::powf(result, fbmParams.Exponent);
    }

    float ANoise::Eval2D(const Vector2 &p) const
    {
        float result = 0.0f;

        float frequency = this->fbmParams.StartFrequency;
        float amplitude = 1.0f;

        float t = 0.0f;

        for(std::uint32_t i = 0; i < this->fbmParams.NumberOfOctaves; i++)
        {
            result += amplitude*this->noise2D(p*frequency);

            t += amplitude;
            frequency *= fbmParams.Lacunarity;
            amplitude *= fbmParams.Persistence;
        }

        if(fbmParams.Normalize)
        {
            result = result / t;
        }
        return std::powf(result, fbmParams.Exponent);
    }

    float ANoise::Eval3D(const Vector3 &p) const
    {
        float result = 0.0f;

        float frequency = this->fbmParams.StartFrequency;
        float amplitude = 1.0f;

        float t = 0.0f;

        for(std::uint32_t i = 0; i < this->fbmParams.NumberOfOctaves; i++)
        {
            result += amplitude*this->noise3D(p*frequency);

            t += amplitude;
            frequency *= this->fbmParams.Lacunarity;
            amplitude *= this->fbmParams.Persistence;
        }

        if(this->fbmParams.Normalize)
        {
            result = result / t;
        }
        return std::powf(result, fbmParams.Exponent);
    }


    void ANoise::SetNumberOfOctaves(std::uint32_t numberOfOctaves)
    {
        this->fbmParams.NumberOfOctaves = numberOfOctaves;
    }

    void ANoise::SetStartFrequency(float startFrequency)
    {
        this->fbmParams.StartFrequency = startFrequency;
    }

    void ANoise::SetLacunarity(float lacunarity)
    {
        this->fbmParams.Lacunarity = lacunarity;
    }

    void ANoise::SetPersistence(float persistence)
    {
        this->fbmParams.Persistence = persistence;
    }

    void ANoise::SetNormalizeFBM(bool normalize)
    {
        this->fbmParams.Normalize = normalize;
    }

    void ANoise::SetExponent(float exponent)
    {
        this->fbmParams.Exponent = exponent;
    }

    void ANoiseGenerator::SeedNoise(std::uint32_t seed)
    {
        this->noiseParams.SeedNoise(seed);
    }
    void ANoiseGenerator::SeedNoise(std::string seed)
    {
        this->noiseParams.SeedNoise(seed);
    }

    void WhiteNoise::SetWhiteNoiseScale(float scale)
    {
        this->noiseParams.WhiteNoiseScale = scale;
    }
}
