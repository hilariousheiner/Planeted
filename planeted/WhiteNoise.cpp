#include "WhiteNoise.h"

namespace Planeted
{

    std::unique_ptr<IField> WhiteNoise1::Clone() const
    {
        return std::make_unique<WhiteNoise1>(*this);
    }
    std::unique_ptr<IField1> WhiteNoise1::Clone1() const
    {
        return std::make_unique<WhiteNoise1>(*this);
    }

    float WhiteNoise1::Eval(const float &p) const
    {
        int pi = std::floor(p * this->whiteNoiseScale);

        uint32_t h = Hash1D(pi, this->seed.GetSeed());

        return HashToSigned(h);
    }


    // -------------------
    WhiteNoise::WhiteNoise()
    {
        this->WhiteNoiseScale = 100.0f;
    }

    std::unique_ptr<ANoise> WhiteNoise::Clone() const
    {
        return std::make_unique<WhiteNoise>(*this);
    }
    void WhiteNoise::SetWhiteNoiseScale(float scale)
    {
        this->WhiteNoiseScale = scale;
    }

    float WhiteNoise::Eval(const float &p) const
    {
        int pi = std::floor(p * this->WhiteNoiseScale);

        uint32_t h = Hash1D(pi, this->seed.GetSeed());

        return HashToSigned(h);
    }
    float WhiteNoise::Eval(const Vector2 &p) const
    {
        int xi = std::floor(p.X * this->WhiteNoiseScale);
        int yi = std::floor(p.Y * this->WhiteNoiseScale);

        uint32_t h = Hash2D(xi, yi, this->seed.GetSeed());

        return HashToSigned(h);
    }
    float WhiteNoise::Eval(const Vector3 &p) const
    {
        int xi = std::floor(p.X * this->WhiteNoiseScale);
        int yi = std::floor(p.Y * this->WhiteNoiseScale);
        int zi = std::floor(p.Z * this->WhiteNoiseScale);

        uint32_t h = Hash3D(xi, yi, zi, this->seed.GetSeed());

        return HashToSigned(h);
    }
}
