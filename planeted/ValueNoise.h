#ifndef PLANETED_VALUENOISE_H
#define PLANETED_VALUENOISE_H

#include "Field.h"
#include "Noise.h"
#include "PermutationTable.h"

namespace Planeted
{
    class ValueNoise1 : public AFieldGenerator1
    {
    public:
        std::unique_ptr<IField> Clone() const override;
        std::unique_ptr<IField1> Clone1() const override;

        float Eval(const float &p) const override;
    };

    class ValueNoise : public ANoiseGenerator
    {
    public:
        std::unique_ptr<ANoise> Clone() const override;

        float Eval(const float &p) const override;
        float Eval(const Vector2 &p) const override;
        float Eval(const Vector3 &p) const override;
    };
}

#endif
