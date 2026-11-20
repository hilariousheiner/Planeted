#ifndef PLANETED_VALUENOISE_H
#define PLANETED_VALUENOISE_H

#include "Field.h"
#include "PermutationTable.h"

namespace Planeted
{
    class ValueNoise1 : public AFieldGenerator1
    {
    public:
        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField1> Clone1() const override;

        float Eval(const float &p) const override;
    };

    class ValueNoise2 : public AFieldGenerator2
    {
    public:
        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField2> Clone2() const override;

        float Eval(const Vector2 &p) const override;
    };

    class ValueNoise3 : public AFieldGenerator3
    {
    public:
        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField3> Clone3() const override;

        float Eval(const Vector3 &p) const override;
    };
}

#endif
