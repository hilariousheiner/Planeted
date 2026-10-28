#include "Field.h"

namespace Planeted
{
    void AFieldGenerator1::SetSeed(std::uint32_t seedValue)
    {
        this->seed = Seed(seedValue);
    }
    void AFieldGenerator1::SetSeed(std::string seedValue)
    {
        this->seed = Seed(seedValue);
    }

    void AFieldGenerator2::SetSeed(std::uint32_t seedValue)
    {
        this->seed = Seed(seedValue);
    }
    void AFieldGenerator2::SetSeed(std::string seedValue)
    {
        this->seed = Seed(seedValue);
    }

    void AFieldGenerator3::SetSeed(std::uint32_t seedValue)
    {
        this->seed = Seed(seedValue);
    }
    void AFieldGenerator3::SetSeed(std::string seedValue)
    {
        this->seed = Seed(seedValue);
    }


    ConstantField1::ConstantField1(float constant)
        : constant(constant)
    { }

    std::unique_ptr<IField1> ConstantField1::Clone() const
    {
        return std::make_unique<ConstantField1>(*this);
    }

    float ConstantField1::Eval(const float &p) const
    {
        return this->constant;
    }

    AbsFieldModifier1::AbsFieldModifier1(std::unique_ptr<IField1> field)
        : field(std::move(field))
    {}

    AbsFieldModifier1::AbsFieldModifier1(const AbsFieldModifier1 &other)
        : IField1(other), field(other.field->Clone())
    {}

    std::unique_ptr<IField1> AbsFieldModifier1::Clone() const
    {
        return std::make_unique<AbsFieldModifier1>(*this);
    }

    float AbsFieldModifier1::Eval(const float &p) const
    {
        return std::abs(this->field->Eval(p));
    }

    void AbsFieldModifier1::SetSeed(std::uint32_t seed)
    {
        this->field->SetSeed(seed);
    }
    void AbsFieldModifier1::SetSeed(std::string seed)
    {
        this->field->SetSeed(seed);
    }

    PowFieldModifier1::PowFieldModifier1(std::unique_ptr<IField1> field, float exponent)
        : field(std::move(field)), exponent(exponent)
    {}

    PowFieldModifier1::PowFieldModifier1(const PowFieldModifier1 &other)
        : IField1(other), field(other.field->Clone()), exponent(other.exponent)
    {}

    std::unique_ptr<IField1> PowFieldModifier1::Clone() const
    {
        return std::make_unique<PowFieldModifier1>(*this);
    }

    float PowFieldModifier1::Eval(const float &p) const
    {
        return std::pow(this->field->Eval(p), this->exponent);
    }

    void PowFieldModifier1::SetSeed(std::uint32_t seed)
    {
        this->field->SetSeed(seed);
    }
    void PowFieldModifier1::SetSeed(std::string seed)
    {
        this->field->SetSeed(seed);
    }


    FBMFieldModifier1::FBMFieldModifier1(std::unique_ptr<IField1> field, const FBMParameters &fbmParameters)
        : field(std::move(field)), fbmParams(fbmParameters)
    { }

    FBMFieldModifier1::FBMFieldModifier1(const FBMFieldModifier1 &other)
        : IField1(other), field(other.field->Clone()), fbmParams(other.fbmParams)
    { }

    std::unique_ptr<IField1> FBMFieldModifier1::Clone() const
    {
        return std::make_unique<FBMFieldModifier1>(*this);
    }

    float FBMFieldModifier1::Eval(const float &p) const
    {
        float result = 0.0f;

        float frequency = this->fbmParams.StartFrequency;
        float amplitude = 1.0f;

        float t = 0.0f;

        for(std::uint32_t i = 0; i < this->fbmParams.NumberOfOctaves; i++)
        {
            result += amplitude*this->field->Eval(p*frequency);

            t += amplitude;
            frequency *= this->fbmParams.Lacunarity;
            amplitude *= this->fbmParams.Persistence;
        }

        if(this->fbmParams.Normalize)
        {
            result = result / t;
        }
        return result;
    }

    void FBMFieldModifier1::SetSeed(std::uint32_t seed)
    {
        this->field->SetSeed(seed);
    }
    void FBMFieldModifier1::SetSeed(std::string seed)
    {
        this->field->SetSeed(seed);
    }
}
