#ifndef PLANETED_WHITENOISE_H
#define PLANETED_WHITENOISE_H

#include "Field.h"
#include "Noise.h"

namespace Planeted
{
    class WhiteNoise : public ANoiseGenerator
    {
    public:
        WhiteNoise();

        void SetWhiteNoiseScale(float scale);
        std::unique_ptr<ANoise> Clone() const override;

        float Eval(const float &p) const override;
        float Eval(const Vector2 &p) const override;
        float Eval(const Vector3 &p) const override;
    private:
        float WhiteNoiseScale;
    };
}
#endif
