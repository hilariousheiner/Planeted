#ifndef PLANETED_NOISE_H
#define PLANETED_NOISE_H

#include <memory>

#include "Random.h"

namespace Planeted
{
    class ANoise
    {
    public:
        virtual ~ANoise() = default;

        float Eval1D(const float &p) const;
        float Eval2D(const Vector2 &p) const;
        float Eval3D(const Vector3 &p) const;

        virtual void SeedNoise(std::uint32_t seed) = 0;
        virtual void SeedNoise(std::string seed) = 0;

        void SetNumberOfOctaves(std::uint32_t numberOfOctaves);
        void SetStartFrequency(float startFrequency);
        void SetLacunarity(float lacunarity);
        void SetPersistence(float persistence);
        void SetNormalizeFBM(bool normalize);
        void SetExponent(float exponent);

    protected:
        virtual float noise1D(const float &p) const = 0;
        virtual float noise2D(const Vector2 &p) const = 0;
        virtual float noise3D(const Vector3 &p) const = 0;

    private:
        Random::FBMParameters fbmParams;
    };

    class ANoiseGenerator : public ANoise
    {
    public:
        void SeedNoise(std::uint32_t seed) override;
        void SeedNoise(std::string seed) override;

    protected:
        Random::NoiseParameters noiseParams;
    };

    class WhiteNoise : public ANoiseGenerator
    {
    public:
        void SetWhiteNoiseScale(float scale);

    protected:
        float noise1D(const float &p) const override;
        float noise2D(const Vector2 &p) const override;
        float noise3D(const Vector3 &p) const override;
    };

    class ValueNoise : public ANoiseGenerator
    {
    protected:
        float noise1D(const float &p) const override;
        float noise2D(const Vector2 &p) const override;
        float noise3D(const Vector3 &p) const override;
    };

    class PerlinNoise : public ANoiseGenerator
    {
    protected:
        float noise1D(const float &p) const override;
        float noise2D(const Vector2 &p) const override;
        float noise3D(const Vector3 &p) const override;
    };

    class RidgeNoiseModifier : public ANoise
    {
    public:
        RidgeNoiseModifier(std::unique_ptr<ANoise> noise);

    protected:
        float noise1D(const float &p) const override;
        float noise2D(const Vector2 &p) const override;
        float noise3D(const Vector3 &p) const override;

    private:
        std::unique_ptr<ANoise> noise;
    };

    class BillowNoiseModifier : public ANoise
    {
    public:
        BillowNoiseModifier(std::unique_ptr<ANoise> noise);

    protected:
        float noise1D(const float &p) const override;
        float noise2D(const Vector2 &p) const override;
        float noise3D(const Vector3 &p) const override;

    private:
        std::unique_ptr<ANoise> noise;
    };
}
#endif
