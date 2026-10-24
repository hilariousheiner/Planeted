#ifndef PLANETED_NOISE_H
#define PLANETED_NOISE_H

#include <memory>

#include "FBM.h"
#include "Random.h"

namespace Planeted
{
    class ANoise
    {
    public:
        virtual ~ANoise() = default;
        virtual std::unique_ptr<ANoise> Clone() const = 0;

        virtual float Eval(const float &p) const;
        virtual float Eval(const Vector2 &p) const;
        virtual float Eval(const Vector3 &p) const;

        virtual void Seed(std::uint32_t seed) = 0;
        virtual void Seed(std::string seed) = 0;

        void SetFBMParameters(const FBMParameters &fbmParameters);

        void SetNumberOfOctaves(std::uint32_t numberOfOctaves);
        void SetStartFrequency(float startFrequency);
        void SetLacunarity(float lacunarity);
        void SetPersistence(float persistence);
        void SetNormalizeFBM(bool normalize);

    protected:
        virtual float noise1D(const float &p) const = 0;
        virtual float noise2D(const Vector2 &p) const = 0;
        virtual float noise3D(const Vector3 &p) const = 0;

    //private:
        FBMParameters fbmParams;
    };

    class ANoiseGenerator : public ANoise
    {
    public:
        void Seed(std::uint32_t seed) override;
        void Seed(std::string seed) override;

    protected:
        Random::NoiseParameters noiseParams;
    };

    class WhiteNoise : public ANoiseGenerator
    {
    public:
        void SetWhiteNoiseScale(float scale);
        std::unique_ptr<ANoise> Clone() const override;

    protected:
        float noise1D(const float &p) const override;
        float noise2D(const Vector2 &p) const override;
        float noise3D(const Vector3 &p) const override;
    };

    class ValueNoise : public ANoiseGenerator
    {
    public:
        std::unique_ptr<ANoise> Clone() const override;

    protected:
        float noise1D(const float &p) const override;
        float noise2D(const Vector2 &p) const override;
        float noise3D(const Vector3 &p) const override;
    };

    class PerlinNoise : public ANoiseGenerator
    {
    public:
        std::unique_ptr<ANoise> Clone() const override;

    protected:
        float noise1D(const float &p) const override;
        float noise2D(const Vector2 &p) const override;
        float noise3D(const Vector3 &p) const override;
    };

    class RidgeNoiseModifier : public ANoise
    {
    public:

        RidgeNoiseModifier(std::unique_ptr<ANoise> noise);

        RidgeNoiseModifier(const RidgeNoiseModifier &other);

        std::unique_ptr<ANoise> Clone() const override;

        void Seed(std::uint32_t seed) override;
        void Seed(std::string seed) override;

    protected:
        float noise1D(const float &p) const override;
        float noise2D(const Vector2 &p) const override;
        float noise3D(const Vector3 &p) const override;

    private:
        std::unique_ptr<ANoise> noise;
    };

    class AbsNoiseModifier : public ANoise
    {
    public:
        AbsNoiseModifier(std::unique_ptr<ANoise> noise);
        AbsNoiseModifier(const AbsNoiseModifier &other);

        std::unique_ptr<ANoise> Clone() const override;

        void Seed(std::uint32_t seed) override;
        void Seed(std::string seed) override;

    protected:
        float noise1D(const float &p) const override;
        float noise2D(const Vector2 &p) const override;
        float noise3D(const Vector3 &p) const override;

    private:
        std::unique_ptr<ANoise> noise;
    };

    class PowNoiseModifier : public ANoise
    {
    public:
        PowNoiseModifier(std::unique_ptr<ANoise> noise, float exponent);
        PowNoiseModifier(const PowNoiseModifier &other);

        std::unique_ptr<ANoise> Clone() const override;

        void Seed(std::uint32_t seed) override;
        void Seed(std::string seed) override;

    protected:
        float noise1D(const float &p) const override;
        float noise2D(const Vector2 &p) const override;
        float noise3D(const Vector3 &p) const override;

    private:
        std::unique_ptr<ANoise> noise;
        float exponent;
    };

    class FBMScalarFieldModifier : public ANoise
    {
    public:
        FBMScalarFieldModifier(std::unique_ptr<ANoise> noise, const FBMParameters &fbmParameters);
        FBMScalarFieldModifier(const FBMScalarFieldModifier &other);

        std::unique_ptr<ANoise> Clone() const override;

        float Eval(const float &p) const override;
        float Eval(const Vector2 &p) const override;
        float Eval(const Vector3 &p) const override;

        void Seed(std::uint32_t seed) override;
        void Seed(std::string seed) override;

    protected:
        float noise1D(const float &p) const override;
        float noise2D(const Vector2 &p) const override;
        float noise3D(const Vector3 &p) const override;

    private:
        std::unique_ptr<ANoise> noise;
    };
}
#endif
