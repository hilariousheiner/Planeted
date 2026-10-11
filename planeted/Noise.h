#ifndef PLANETED_NOISE_H
#define PLANETED_NOISE_H

#include "Random.h"

namespace Planeted
{
    class ANoise
    {
    public:
        virtual ~ANoise() {}

        float Eval1D(const float &p) const;
        float Eval2D(const Vector2 &p) const;
        float Eval3D(const Vector3 &p) const;

    protected:
        virtual float noise1D(const float &p) const = 0;
        virtual float noise2D(const Vector2 &p) const = 0;
        virtual float noise3D(const Vector3 &p) const = 0;

    private:
        Random::FBMParameters fbmParams;
    };

    struct WhiteNoise : ANoise
    {
    public:

    };
}
#endif
