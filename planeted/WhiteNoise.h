#ifndef PLANETED_WHITENOISE_H
#define PLANETED_WHITENOISE_H

#include "Field.h"
#include "Noise.h"

namespace Planeted
{
    class WhiteNoise1 : public AFieldGenerator1
    {
    public:
        WhiteNoise1();

        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField1> Clone1() const override;

        PLTypeInfo* GetTypeInfo(const PDSL_Runtime &runtime) const override;

        void SetWhiteNoiseScale(float scale);

        float Eval(const float &p) const override;

    private:
        float whiteNoiseScale;
    };

    class WhiteNoise2 : public AFieldGenerator2
    {
    public:
        WhiteNoise2();

        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField2> Clone2() const override;

        PLTypeInfo* GetTypeInfo(const PDSL_Runtime &runtime) const override;

        void SetWhiteNoiseScale(float scale);

        float Eval(const Vector2 &p) const override;

    private:
        float whiteNoiseScale;
    };

    class WhiteNoise3 : public AFieldGenerator3
    {
    public:
        WhiteNoise3();

        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField3> Clone3() const override;

        PLTypeInfo* GetTypeInfo(const PDSL_Runtime &runtime) const override;

        void SetWhiteNoiseScale(float scale);

        float Eval(const Vector3 &p) const override;

    private:
        float whiteNoiseScale;
    };
}
#endif
