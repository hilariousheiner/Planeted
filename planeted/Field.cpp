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
}
