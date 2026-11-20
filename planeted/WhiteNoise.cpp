#include "WhiteNoise.h"
#include "PDSL.h"

namespace Planeted
{
    WhiteNoise1::WhiteNoise1()
    {
        this->whiteNoiseScale = 100.0f;
    }

    std::unique_ptr<AField> WhiteNoise1::Clone() const
    {
        return std::make_unique<WhiteNoise1>(*this);
    }
    std::unique_ptr<AField1> WhiteNoise1::Clone1() const
    {
        return std::make_unique<WhiteNoise1>(*this);
    }

    float WhiteNoise1::Eval(const float &p) const
    {
        int pi = std::floor(p * this->whiteNoiseScale);

        uint32_t h = Hash1D(pi, this->seed.GetSeed());

        return HashToSigned(h);
    }

    PLTypeInfo* WhiteNoise1::GetTypeInfo(const PDSL_Runtime &runtime) const
    {
        return runtime.FieldsMod->GetWhiteNoise1TypeInfo();
    }

    void WhiteNoise1::SetWhiteNoiseScale(float scale)
    {
        this->whiteNoiseScale = scale;
    }


    WhiteNoise2::WhiteNoise2()
    {
        this->whiteNoiseScale = 100.0f;
    }

    std::unique_ptr<AField> WhiteNoise2::Clone() const
    {
        return std::make_unique<WhiteNoise2>(*this);
    }
    std::unique_ptr<AField2> WhiteNoise2::Clone2() const
    {
        return std::make_unique<WhiteNoise2>(*this);
    }

    float WhiteNoise2::Eval(const Vector2 &p) const
    {
        int xi = std::floor(p.X * this->whiteNoiseScale);
        int yi = std::floor(p.Y * this->whiteNoiseScale);

        uint32_t h = Hash2D(xi, yi, this->seed.GetSeed());

        return HashToSigned(h);
    }

    PLTypeInfo* WhiteNoise2::GetTypeInfo(const PDSL_Runtime &runtime) const
    {
        return runtime.FieldsMod->GetWhiteNoise2TypeInfo();
    }

    void WhiteNoise2::SetWhiteNoiseScale(float scale)
    {
        this->whiteNoiseScale = scale;
    }

    // -------------------

    WhiteNoise3::WhiteNoise3()
    {
        this->whiteNoiseScale = 100.0f;
    }

    std::unique_ptr<AField> WhiteNoise3::Clone() const
    {
        return std::make_unique<WhiteNoise3>(*this);
    }
    std::unique_ptr<AField3> WhiteNoise3::Clone3() const
    {
        return std::make_unique<WhiteNoise3>(*this);
    }

    float WhiteNoise3::Eval(const Vector3 &p) const
    {
        int xi = std::floor(p.X * this->whiteNoiseScale);
        int yi = std::floor(p.Y * this->whiteNoiseScale);
        int zi = std::floor(p.Z * this->whiteNoiseScale);

        uint32_t h = Hash3D(xi, yi, zi, this->seed.GetSeed());

        return HashToSigned(h);
    }

    PLTypeInfo* WhiteNoise3::GetTypeInfo(const PDSL_Runtime &runtime) const
    {
        return runtime.FieldsMod->GetWhiteNoise3TypeInfo();
    }

    void WhiteNoise3::SetWhiteNoiseScale(float scale)
    {
        this->whiteNoiseScale = scale;
    }
}
