#ifndef PLANETED_PERLINNOISE_H
#define PLANETED_PERLINNOISE_H

#include "Noise.h"

namespace Planeted
{
    class PerlinNoise : public ANoiseGenerator
    {
    public:
        std::unique_ptr<ANoise> Clone() const override;

        float Eval(const float &p) const override;
        float Eval(const Vector2 &p) const override;
        float Eval(const Vector3 &p) const override;
    };
}
#endif
