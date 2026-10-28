#ifndef PLANETED_NOISEVALUE_H
#define PLANETED_NOISEVALUE_H

namespace Planeted
{
    class NoiseValue
    {
    public:
        NoiseValue() = default;

        explicit NoiseValue(std::unique_ptr<ANoise> noise)
            : noise(std::move(noise))
        {}

        NoiseValue(const NoiseValue &other)
            : noise(other.noise->Clone())
        {}

        NoiseValue &operator=(const NoiseValue &other)
        {
            if(this != &other)
            {
                this->noise = other.noise->Clone();
            }
            return *this;
        }

        NoiseValue(NoiseValue&&) noexcept = default;
        NoiseValue& operator=(NoiseValue&&) noexcept = default;

        ANoise &Get()
        {
            return *noise;
        }

    private:
        std::unique_ptr<ANoise> noise;
    };
}
#endif
