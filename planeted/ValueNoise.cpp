#include "ValueNoise.h"
#include "Math.h"

namespace Planeted
{
    std::unique_ptr<ANoise> ValueNoise::Clone() const
    {
        return std::make_unique<ValueNoise>(*this);
    }

    float ValueNoise::Eval(const float &p) const
    {
        int pi = FloorToInt(p);

        std::uint8_t p0 = PermutationTable::ToGrid(pi);
        std::uint8_t p1 = PermutationTable::ToGrid(p0 + 1);

        const float &c0 = HashToSigned(Hash1D(p0, this->seed.GetSeed()));
        const float &c1 = HashToSigned(Hash1D(p1, this->seed.GetSeed()));

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

        const float &c00 = HashToSigned(Hash2D(xi0, yi0, this->seed.GetSeed()));
        const float &c10 = HashToSigned(Hash2D(xi1, yi0, this->seed.GetSeed()));
        const float &c01 = HashToSigned(Hash2D(xi0, yi1, this->seed.GetSeed()));
        const float &c11 = HashToSigned(Hash2D(xi1, yi1, this->seed.GetSeed()));

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
        const float &c000 = HashToSigned(Hash3D(xi0, yi0, zi0, this->seed.GetSeed()));
        const float &c100 = HashToSigned(Hash3D(xi1, yi0, zi0, this->seed.GetSeed()));
        const float &c010 = HashToSigned(Hash3D(xi0, yi1, zi0, this->seed.GetSeed()));
        const float &c110 = HashToSigned(Hash3D(xi1, yi1, zi0, this->seed.GetSeed()));

        const float &c001 = HashToSigned(Hash3D(xi0, yi0, zi1, this->seed.GetSeed()));
        const float &c101 = HashToSigned(Hash3D(xi1, yi0, zi1, this->seed.GetSeed()));
        const float &c011 = HashToSigned(Hash3D(xi0, yi1, zi1, this->seed.GetSeed()));
        const float &c111 = HashToSigned(Hash3D(xi1, yi1, zi1, this->seed.GetSeed()));

        // interpolate:
        float u00 = SmoothStepUnclamped(c000, c100, tx);
        float u10 = SmoothStepUnclamped(c010, c110, tx);

        float u01 = SmoothStepUnclamped(c001, c101, tx);
        float u11 = SmoothStepUnclamped(c011, c111, tx);

        float v0 = SmoothStepUnclamped(u00, u10, ty);
        float v1 = SmoothStepUnclamped(u01, u11, ty);

        return SmoothStepUnclamped(v0, v1, tz);
    }
}
