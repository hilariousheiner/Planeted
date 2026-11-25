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

    //---------------------------------

    FieldSum2::FieldSum2(std::unique_ptr<AField2> fieldA, std::unique_ptr<AField2> fieldB)
        : fieldA(std::move(fieldA)), fieldB(std::move(fieldB))
    {}

    FieldSum2::FieldSum2(const FieldSum2 &other)
        : AField2(other), fieldA(other.fieldA->Clone2()), fieldB(other.fieldB->Clone2())
    {}

    std::unique_ptr<AField> FieldSum2::Clone() const
    {
        return std::make_unique<FieldSum2>(*this);
    }
    std::unique_ptr<AField2> FieldSum2::Clone2() const
    {
        return std::make_unique<FieldSum2>(*this);
    }

    float FieldSum2::Eval(const Vector2 &p) const
    {
        return this->fieldA->Eval(p) + this->fieldB->Eval(p);
    }

    void FieldSum2::SetSeed(std::uint32_t seed)
    {
        this->fieldA->SetSeed(seed);
        this->fieldB->SetSeed(seed);
    }
    void FieldSum2::SetSeed(std::string seed)
    {
        this->fieldA->SetSeed(seed);
        this->fieldB->SetSeed(seed);
    }

    //---------------------------------

    FieldSum3::FieldSum3(std::unique_ptr<AField3> fieldA, std::unique_ptr<AField3> fieldB)
        : fieldA(std::move(fieldA)), fieldB(std::move(fieldB))
    {}

    FieldSum3::FieldSum3(const FieldSum3 &other)
        : AField3(other), fieldA(other.fieldA->Clone3()), fieldB(other.fieldB->Clone3())
    {}

    std::unique_ptr<AField> FieldSum3::Clone() const
    {
        return std::make_unique<FieldSum3>(*this);
    }
    std::unique_ptr<AField3> FieldSum3::Clone3() const
    {
        return std::make_unique<FieldSum3>(*this);
    }

    float FieldSum3::Eval(const Vector3 &p) const
    {
        return this->fieldA->Eval(p) + this->fieldB->Eval(p);
    }

    void FieldSum3::SetSeed(std::uint32_t seed)
    {
        this->fieldA->SetSeed(seed);
        this->fieldB->SetSeed(seed);
    }
    void FieldSum3::SetSeed(std::string seed)
    {
        this->fieldA->SetSeed(seed);
        this->fieldB->SetSeed(seed);
    }
}
