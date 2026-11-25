#include "FieldArithmetic.h"

namespace Planeted
{
    FieldSum1::FieldSum1(std::unique_ptr<AField1> fieldA, std::unique_ptr<AField1> fieldB)
        : fieldA(std::move(fieldA)), fieldB(std::move(fieldB))
    {}

    FieldSum1::FieldSum1(const FieldSum1 &other)
        : AField1(other), fieldA(other.fieldA->Clone1()), fieldB(other.fieldB->Clone1())
    {}

    std::unique_ptr<AField> FieldSum1::Clone() const
    {
        return std::make_unique<FieldSum1>(*this);
    }
    std::unique_ptr<AField1> FieldSum1::Clone1() const
    {
        return std::make_unique<FieldSum1>(*this);
    }

    float FieldSum1::Eval(const float &p) const
    {
        return this->fieldA->Eval(p) + this->fieldB->Eval(p);
    }

    void FieldSum1::SetSeed(std::uint32_t seed)
    {
        this->fieldA->SetSeed(seed);
        this->fieldB->SetSeed(seed);
    }
    void FieldSum1::SetSeed(std::string seed)
    {
        this->fieldA->SetSeed(seed);
        this->fieldB->SetSeed(seed);
    }
}
