#include "Math.h"
#include "Noise.h"
#include "PermutationTable.h"
#include "PRNG.h"

namespace Planeted
{
    void ANoiseGenerator::SetSeed(std::uint32_t seedValue)
    {
        this->seed = Seed(seedValue);
    }
    void ANoiseGenerator::SetSeed(std::string seedValue)
    {
        this->seed = Seed(seedValue);
    }




    RidgeNoiseModifier::RidgeNoiseModifier(std::unique_ptr<ANoise> noise)
        : noise(std::move(noise))
    {}

    RidgeNoiseModifier::RidgeNoiseModifier(const RidgeNoiseModifier &other)
        : ANoise(other), noise(other.noise->Clone())
    {}

    std::unique_ptr<ANoise> RidgeNoiseModifier::Clone() const
    {
        return std::make_unique<RidgeNoiseModifier>(*this);
    }

    float RidgeNoiseModifier::Eval(const float &p) const
    {
        float n = (0.9f - std::abs(this->noise->Eval(p)));
        return n*n;
    }
    float RidgeNoiseModifier::Eval(const Vector2 &p) const
    {
        float n = (0.9f - std::abs(this->noise->Eval(p)));
        return n*n;
    }
    float RidgeNoiseModifier::Eval(const Vector3 &p) const
    {
        float n = (0.9f - std::abs(this->noise->Eval(p)));
        return n*n;
    }

    void RidgeNoiseModifier::SetSeed(std::uint32_t seed)
    {
        this->noise->SetSeed(seed);
    }
    void RidgeNoiseModifier::SetSeed(std::string seed)
    {
        this->noise->SetSeed(seed);
    }

    AbsNoiseModifier::AbsNoiseModifier(std::unique_ptr<ANoise> noise)
        : noise(std::move(noise))
    {}

    AbsNoiseModifier::AbsNoiseModifier(const AbsNoiseModifier &other)
        : ANoise(other), noise(other.noise->Clone())
    {}

    std::unique_ptr<ANoise> AbsNoiseModifier::Clone() const
    {
        return std::make_unique<AbsNoiseModifier>(*this);
    }

    float AbsNoiseModifier::Eval(const float &p) const
    {
        return std::abs(this->noise->Eval(p));
    }
    float AbsNoiseModifier::Eval(const Vector2 &p) const
    {
         return std::abs(this->noise->Eval(p));
    }
    float AbsNoiseModifier::Eval(const Vector3 &p) const
    {
         return std::abs(this->noise->Eval(p));
    }

    void AbsNoiseModifier::SetSeed(std::uint32_t seed)
    {
        this->noise->SetSeed(seed);
    }
    void AbsNoiseModifier::SetSeed(std::string seed)
    {
        this->noise->SetSeed(seed);
    }

    PowNoiseModifier::PowNoiseModifier(std::unique_ptr<ANoise> noise, float exponent)
        : noise(std::move(noise)), exponent(exponent)
    {}

    PowNoiseModifier::PowNoiseModifier(const PowNoiseModifier &other)
        : ANoise(other), noise(other.noise->Clone()), exponent(other.exponent)
    {}

    std::unique_ptr<ANoise> PowNoiseModifier::Clone() const
    {
        return std::make_unique<PowNoiseModifier>(*this);
    }

    float PowNoiseModifier::Eval(const float &p) const
    {
        return std::pow(this->noise->Eval(p), this->exponent);
    }
    float PowNoiseModifier::Eval(const Vector2 &p) const
    {
        return std::pow(this->noise->Eval(p), this->exponent);
    }
    float PowNoiseModifier::Eval(const Vector3 &p) const
    {
        return std::pow(this->noise->Eval(p), this->exponent);
    }

    void PowNoiseModifier::SetSeed(std::uint32_t seed)
    {
        this->noise->SetSeed(seed);
    }
    void PowNoiseModifier::SetSeed(std::string seed)
    {
        this->noise->SetSeed(seed);
    }

    FBMNoiseModifier::FBMNoiseModifier(std::unique_ptr<ANoise> noise, const FBMParameters &fbmParameters)
        : noise(std::move(noise)), fbmParams(fbmParameters)
    { }

    FBMNoiseModifier::FBMNoiseModifier(const FBMNoiseModifier &other)
        : ANoise(other), noise(other.noise->Clone()), fbmParams(other.fbmParams)
    { }

    std::unique_ptr<ANoise> FBMNoiseModifier::Clone() const
    {
        return std::make_unique<FBMNoiseModifier>(*this);
    }

    float FBMNoiseModifier::Eval(const float &p) const
    {
        float result = 0.0f;

        float frequency = this->fbmParams.StartFrequency;
        float amplitude = 1.0f;

        float t = 0.0f;

        for(std::uint32_t i = 0; i < this->fbmParams.NumberOfOctaves; i++)
        {
            result += amplitude*this->noise->Eval(p*frequency);

            t += amplitude;
            frequency *= this->fbmParams.Lacunarity;
            amplitude *= this->fbmParams.Persistence;
        }

        if(this->fbmParams.Normalize)
        {
            result = result / t;
        }
        return result;
    }
    float FBMNoiseModifier::Eval(const Vector2 &p) const
    {
        float result = 0.0f;

        float frequency = this->fbmParams.StartFrequency;
        float amplitude = 1.0f;

        float t = 0.0f;

        for(std::uint32_t i = 0; i < this->fbmParams.NumberOfOctaves; i++)
        {
            result += amplitude*this->noise->Eval(p*frequency);

            t += amplitude;
            frequency *= fbmParams.Lacunarity;
            amplitude *= fbmParams.Persistence;
        }

        if(fbmParams.Normalize)
        {
            result = result / t;
        }
        return result;
    }
    float FBMNoiseModifier::Eval(const Vector3 &p) const
    {
        float result = 0.0f;

        float frequency = this->fbmParams.StartFrequency;
        float amplitude = 1.0f;

        float t = 0.0f;

        for(std::uint32_t i = 0; i < this->fbmParams.NumberOfOctaves; i++)
        {
            result += amplitude*this->noise->Eval(p*frequency);

            t += amplitude;
            frequency *= this->fbmParams.Lacunarity;
            amplitude *= this->fbmParams.Persistence;
        }

        if(this->fbmParams.Normalize)
        {
            result = result / t;
        }
        return result;
    }

    void FBMNoiseModifier::SetSeed(std::uint32_t seed)
    {
        this->noise->SetSeed(seed);
    }
    void FBMNoiseModifier::SetSeed(std::string seed)
    {
        this->noise->SetSeed(seed);
    }
}
