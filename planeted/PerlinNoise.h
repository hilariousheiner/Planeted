#ifndef PLANETED_PERLINNOISE_H
#define PLANETED_PERLINNOISE_H

#include "Field.h"
#include "Noise.h"
#include "PermutationTable.h"

namespace Planeted
{
    class PerlinNoise1 : public AFieldGenerator1
    {
    public:
        std::unique_ptr<IField1> Clone() const override;

        float Eval(const float &p) const override;

        void SetSeed(std::uint32_t seedValue) override;
        void SetSeed(std::string seedValue) override;

    private:
        PermutationTable permutationTable;

        const float randomDotGrad(const std::uint8_t &x, const float tx) const;
    };

    class PerlinNoise : public ANoiseGenerator
    {
    public:
        std::unique_ptr<ANoise> Clone() const override;

        float Eval(const float &p) const override;
        float Eval(const Vector2 &p) const override;
        float Eval(const Vector3 &p) const override;

        void SetSeed(std::uint32_t seedValue) override;
        void SetSeed(std::string seedValue) override;

    private:
        PermutationTable permutationTable;

        const float randomDotGrad(const std::uint8_t &x, const float tx) const;
        const float randomDotGrad(const int &x, const int &y, const float tx, const float ty) const;
        const float randomDotGrad(const int &x, const int &y, const int &z, const float tx, const float ty, const float tz) const;
    };
}
#endif
