#include "Noise.h"
#include "PRNG.h"

namespace Planeted
{
    void ANoiseGenerator::SetSeed(std::uint32_t seed)
    {
        this->noiseParams.SetSeed(seed);
    }
    void ANoiseGenerator::SetSeed(std::string seed)
    {
        this->noiseParams.SetSeed(seed);
    }

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

        uint32_t h = Hash1D(pi, this->noiseParams.seed);

        return HashToSigned(h);
    }
    float WhiteNoise::Eval(const Vector2 &p) const
    {
        int xi = std::floor(p.X * this->WhiteNoiseScale);
        int yi = std::floor(p.Y * this->WhiteNoiseScale);

        uint32_t h = Hash2D(xi, yi, this->noiseParams.seed);

        return HashToSigned(h);
    }
    float WhiteNoise::Eval(const Vector3 &p) const
    {
        int xi = std::floor(p.X * this->WhiteNoiseScale);
        int yi = std::floor(p.Y * this->WhiteNoiseScale);
        int zi = std::floor(p.Z * this->WhiteNoiseScale);

        uint32_t h = Hash3D(xi, yi, zi, this->noiseParams.seed);

        return HashToSigned(h);
    }

    std::unique_ptr<ANoise> ValueNoise::Clone() const
    {
        return std::make_unique<ValueNoise>(*this);
    }

    float ValueNoise::Eval(const float &p) const
    {
        int pi = FloorToInt(p);

        std::uint8_t p0 = PermutationTable::ToGrid(pi);
        std::uint8_t p1 = PermutationTable::ToGrid(p0 + 1);

        const float &c0 = HashToSigned(Hash1D(p0, this->noiseParams.seed));
        const float &c1 = HashToSigned(Hash1D(p1, this->noiseParams.seed));

        return SmoothStepUnclamped(c0, c1, p - pi);
    }
    float ValueNoise::Eval(const Vector2 &p) const
    {
        int xi = FloorToInt(p.X);
        int yi = FloorToInt(p.Y);

        int xi0 = PermutationTable::ToGrid(xi);
        int yi0 = PermutationTable::ToGrid(yi);

        int xi1 = PermutationTable::ToGrid(xi0 + 1);
        int yi1 = PermutationTable::ToGrid(yi0 + 1);

        float tx = p.X - xi;
        float ty = p.Y - yi;

        const float &c00 = HashToSigned(Hash2D(xi0, yi0, this->noiseParams.seed));
        const float &c10 = HashToSigned(Hash2D(xi1, yi0, this->noiseParams.seed));
        const float &c01 = HashToSigned(Hash2D(xi0, yi1, this->noiseParams.seed));
        const float &c11 = HashToSigned(Hash2D(xi1, yi1, this->noiseParams.seed));

        float u0 = SmoothStepUnclamped(c00, c10, tx);
        float u1 = SmoothStepUnclamped(c01, c11, tx);

        return SmoothStepUnclamped(u0, u1, ty);
    }
    float ValueNoise::Eval(const Vector3 &p) const
    {
        // calculate grid cell corner coordinates:
        int xi = FloorToInt(p.X);
        int yi = FloorToInt(p.Y);
        int zi = FloorToInt(p.Z);

        int xi0 = PermutationTable::ToGrid(xi);
        int yi0 = PermutationTable::ToGrid(yi);
        int zi0 = PermutationTable::ToGrid(zi);

        int xi1 = PermutationTable::ToGrid(xi0 + 1);
        int yi1 = PermutationTable::ToGrid(yi0 + 1);
        int zi1 = PermutationTable::ToGrid(zi0 + 1);

        float tx = p.X - xi;
        float ty = p.Y - yi;
        float tz = p.Z - zi;

        // get noise value at cell corners:
        const float &c000 = HashToSigned(Hash3D(xi0, yi0, zi0, this->noiseParams.seed));
        const float &c100 = HashToSigned(Hash3D(xi1, yi0, zi0, this->noiseParams.seed));
        const float &c010 = HashToSigned(Hash3D(xi0, yi1, zi0, this->noiseParams.seed));
        const float &c110 = HashToSigned(Hash3D(xi1, yi1, zi0, this->noiseParams.seed));

        const float &c001 = HashToSigned(Hash3D(xi0, yi0, zi1, this->noiseParams.seed));
        const float &c101 = HashToSigned(Hash3D(xi1, yi0, zi1, this->noiseParams.seed));
        const float &c011 = HashToSigned(Hash3D(xi0, yi1, zi1, this->noiseParams.seed));
        const float &c111 = HashToSigned(Hash3D(xi1, yi1, zi1, this->noiseParams.seed));

        // interpolate:
        float u00 = SmoothStepUnclamped(c000, c100, tx);
        float u10 = SmoothStepUnclamped(c010, c110, tx);

        float u01 = SmoothStepUnclamped(c001, c101, tx);
        float u11 = SmoothStepUnclamped(c011, c111, tx);

        float v0 = SmoothStepUnclamped(u00, u10, ty);
        float v1 = SmoothStepUnclamped(u01, u11, ty);

        return SmoothStepUnclamped(v0, v1, tz);
    }

    std::unique_ptr<ANoise> PerlinNoise::Clone() const
    {
        return std::make_unique<PerlinNoise>(*this);
    }
    static const float randomDotGradPerlin(const Random::NoiseParameters &params, const std::uint8_t &x, const float tx)
    {
        return params.Permute(x) & 1 ? tx : -tx;
    }
    float PerlinNoise::Eval(const float &p) const
    {
        int pi = FloorToInt(p);

        std::uint8_t p0 = PermutationTable::ToGrid(pi);
        std::uint8_t p1 = PermutationTable::ToGrid(p0 + 1);

        float tp = p - pi;

        const float g0 = randomDotGradPerlin(this->noiseParams, p0, tp);
        const float g1 = randomDotGradPerlin(this->noiseParams, p1, tp - 1);

        return SmoothStepUnclamped5(g0, g1, tp);
    }

    static float randomDotGradPerlin(const Random::NoiseParameters &params, const int &x, const int &y, const float tx, const float ty)
    {
        float result;

        switch(params.Permute(x, y) & 7)
        {
        case 0:
            result = tx; // (1, 0) * (tx, ty)
            break;
        case 1:
            result = -tx; // (-1, 0) * (tx, ty)
            break;
        case 2:
            result = ty; // (0, 1) * (tx, ty)
            break;
        case 3:
            result = -ty; // (0, -1) * (tx, ty)
            break;
        case 4:
            result = tx + ty; // (1, 1) * (tx, ty)
            break;
        case 5:
            result = -tx + ty; // (-1, 1) * (tx, ty)
            break;
        case 6:
            result = tx - ty; // (1, -1) * (tx, ty)
            break;
        case 7:
            result = -tx - ty; // (-1, -1) * (tx, ty)
            break;
        default:
            break;
        }
        return result;
    }
    float PerlinNoise::Eval(const Vector2 &p) const
    {
        int xi = FloorToInt(p.X);
        int yi = FloorToInt(p.Y);

        int xi0 = PermutationTable::ToGrid(xi);
        int yi0 = PermutationTable::ToGrid(yi);

        int xi1 = PermutationTable::ToGrid(xi0 + 1);
        int yi1 = PermutationTable::ToGrid(yi0 + 1);

        float tx = p.X - xi;
        float ty = p.Y - yi;

        const float &c00 = randomDotGradPerlin(this->noiseParams, xi0, yi0, tx    , ty    );
        const float &c10 = randomDotGradPerlin(this->noiseParams, xi1, yi0, tx - 1, ty    );
        const float &c01 = randomDotGradPerlin(this->noiseParams, xi0, yi1, tx    , ty - 1);
        const float &c11 = randomDotGradPerlin(this->noiseParams, xi1, yi1, tx - 1, ty - 1);

        float u0 = SmoothStepUnclamped5(c00, c10, tx);
        float u1 = SmoothStepUnclamped5(c01, c11, tx);

        return SmoothStepUnclamped5(u0, u1, ty);
    }

    static float randomDotGradPerlin(const Random::NoiseParameters &params, const int &x, const int &y, const int &z, const float tx, const float ty, const float tz)
    {
        float result;

        switch(params.Permute(x,y,z) & 15)
        {
        case 0:
            result = tx + ty; //(1,1,0) * (tx, ty, tz)
            break;
        case 1:
            result = -tx + ty; //(-1,1,0) * (tx, ty, tz)
            break;
        case 2:
            result = tx - ty;  //(1,-1,0) * (tx, ty, tz)
            break;
        case 3:
            result = -tx - ty;//(-1,-1,0) * (tx, ty, tz)
            break;
        case 4:
            result = tx + tz; //(1,0,1) * (tx, ty, tz)
            break;
        case 5:
            result = -tx + tz; //(-1,0,1) * (tx, ty, tz)
            break;
        case 6:
            result = tx - tz; //(1,0,-1) * (tx, ty, tz)
            break;
        case 7:
            result = -tx - tz;//(-1,0,-1) * (tx, ty, tz)
            break;
        case 8:
            result = ty + tz; //(0,1,1) * (tx, ty, tz)
            break;
        case 9:
            result = -ty + tz; //(0,-1,1) * (tx, ty, tz)
            break;
        case 10:
            result = ty - tz; //(0,1,-1) * (tx, ty, tz)
            break;
        case 11:
            result = -ty - tz; //(0,-1,-1) * (tx, ty, tz)
            break;
        case 12:
            result = tx + ty; //(1,1,0) * (tx, ty, tz)
            break;
        case 13:
            result = -tx + ty; //(-1,1,0) * (tx, ty, tz)
            break;
        case 14:
            result = -ty + tz; //(0,-1,1) * (tx, ty, tz)
            break;
        case 15:
            result = -ty - tz; //(0,-1,-1) * (tx, ty, tz)
            break;
        }
        return result;
    }
    float PerlinNoise::Eval(const Vector3 &p) const
    {
        // calculate grid cell corner coordinates:
        int xi = FloorToInt(p.X);
        int yi = FloorToInt(p.Y);
        int zi = FloorToInt(p.Z);

        int xi0 = PermutationTable::ToGrid(xi);
        int yi0 = PermutationTable::ToGrid(yi);
        int zi0 = PermutationTable::ToGrid(zi);

        int xi1 = PermutationTable::ToGrid(xi0 + 1);
        int yi1 = PermutationTable::ToGrid(yi0 + 1);
        int zi1 = PermutationTable::ToGrid(zi0 + 1);

        float tx = p.X - xi;
        float ty = p.Y - yi;
        float tz = p.Z - zi;

        // compute dot products with gradients at cell corners:
        const float &c000 = randomDotGradPerlin(this->noiseParams, xi0, yi0, zi0, tx    , ty    , tz   );
        const float &c100 = randomDotGradPerlin(this->noiseParams, xi1, yi0, zi0, tx - 1, ty    , tz   );
        const float &c010 = randomDotGradPerlin(this->noiseParams, xi0, yi1, zi0, tx    , ty - 1, tz   );
        const float &c110 = randomDotGradPerlin(this->noiseParams, xi1, yi1, zi0, tx - 1, ty - 1, tz   );

        const float &c001 = randomDotGradPerlin(this->noiseParams, xi0, yi0, zi1, tx    , ty    , tz - 1);
        const float &c101 = randomDotGradPerlin(this->noiseParams, xi1, yi0, zi1, tx - 1, ty    , tz - 1);
        const float &c011 = randomDotGradPerlin(this->noiseParams, xi0, yi1, zi1, tx    , ty - 1, tz - 1);
        const float &c111 = randomDotGradPerlin(this->noiseParams, xi1, yi1, zi1, tx - 1, ty - 1, tz - 1);

        // interpolate:
        float u00 = SmoothStepUnclamped5(c000, c100, tx);
        float u10 = SmoothStepUnclamped5(c010, c110, tx);

        float u01 = SmoothStepUnclamped5(c001, c101, tx);
        float u11 = SmoothStepUnclamped5(c011, c111, tx);

        float v0 = SmoothStepUnclamped5(u00, u10, ty);
        float v1 = SmoothStepUnclamped5(u01, u11, ty);

        return SmoothStepUnclamped5(v0, v1, tz);
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

    FBMScalarFieldModifier::FBMScalarFieldModifier(std::unique_ptr<ANoise> noise, const FBMParameters &fbmParameters)
        : noise(std::move(noise)), fbmParams(fbmParameters)
    { }

    FBMScalarFieldModifier::FBMScalarFieldModifier(const FBMScalarFieldModifier &other)
        : ANoise(other), noise(other.noise->Clone()), fbmParams(other.fbmParams)
    { }

    std::unique_ptr<ANoise> FBMScalarFieldModifier::Clone() const
    {
        return std::make_unique<FBMScalarFieldModifier>(*this);
    }

    float FBMScalarFieldModifier::Eval(const float &p) const
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
    float FBMScalarFieldModifier::Eval(const Vector2 &p) const
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
    float FBMScalarFieldModifier::Eval(const Vector3 &p) const
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

    void FBMScalarFieldModifier::SetSeed(std::uint32_t seed)
    {
        this->noise->SetSeed(seed);
    }
    void FBMScalarFieldModifier::SetSeed(std::string seed)
    {
        this->noise->SetSeed(seed);
    }
}
