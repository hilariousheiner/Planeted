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

    //---------------------------------------

    FieldProduct1::FieldProduct1(std::unique_ptr<AField1> fieldA, std::unique_ptr<AField1> fieldB)
        : fieldA(std::move(fieldA)), fieldB(std::move(fieldB))
    {}

    FieldProduct1::FieldProduct1(const FieldProduct1 &other)
        : AField1(other), fieldA(other.fieldA->Clone1()), fieldB(other.fieldB->Clone1())
    {}

    std::unique_ptr<AField> FieldProduct1::Clone() const
    {
        return std::make_unique<FieldProduct1>(*this);
    }
    std::unique_ptr<AField1> FieldProduct1::Clone1() const
    {
        return std::make_unique<FieldProduct1>(*this);
    }

    float FieldProduct1::Eval(const float &p) const
    {
        return this->fieldA->Eval(p) * this->fieldB->Eval(p);
    }

    void FieldProduct1::SetSeed(std::uint32_t seed)
    {
        this->fieldA->SetSeed(seed);
        this->fieldB->SetSeed(seed);
    }
    void FieldProduct1::SetSeed(std::string seed)
    {
        this->fieldA->SetSeed(seed);
        this->fieldB->SetSeed(seed);
    }


    FieldProduct2::FieldProduct2(std::unique_ptr<AField2> fieldA, std::unique_ptr<AField2> fieldB)
        : fieldA(std::move(fieldA)), fieldB(std::move(fieldB))
    {}

    FieldProduct2::FieldProduct2(const FieldProduct2 &other)
        : AField2(other), fieldA(other.fieldA->Clone2()), fieldB(other.fieldB->Clone2())
    {}

    std::unique_ptr<AField> FieldProduct2::Clone() const
    {
        return std::make_unique<FieldProduct2>(*this);
    }
    std::unique_ptr<AField2> FieldProduct2::Clone2() const
    {
        return std::make_unique<FieldProduct2>(*this);
    }

    float FieldProduct2::Eval(const Vector2 &p) const
    {
        return this->fieldA->Eval(p) * this->fieldB->Eval(p);
    }

    void FieldProduct2::SetSeed(std::uint32_t seed)
    {
        this->fieldA->SetSeed(seed);
        this->fieldB->SetSeed(seed);
    }
    void FieldProduct2::SetSeed(std::string seed)
    {
        this->fieldA->SetSeed(seed);
        this->fieldB->SetSeed(seed);
    }

    //-------------
    FieldProduct3::FieldProduct3(std::unique_ptr<AField3> fieldA, std::unique_ptr<AField3> fieldB)
        : fieldA(std::move(fieldA)), fieldB(std::move(fieldB))
    {}

    FieldProduct3::FieldProduct3(const FieldProduct3 &other)
        : AField3(other), fieldA(other.fieldA->Clone3()), fieldB(other.fieldB->Clone3())
    {}

    std::unique_ptr<AField> FieldProduct3::Clone() const
    {
        return std::make_unique<FieldProduct3>(*this);
    }
    std::unique_ptr<AField3> FieldProduct3::Clone3() const
    {
        return std::make_unique<FieldProduct3>(*this);
    }

    float FieldProduct3::Eval(const Vector3 &p) const
    {
        return this->fieldA->Eval(p) * this->fieldB->Eval(p);
    }

    void FieldProduct3::SetSeed(std::uint32_t seed)
    {
        this->fieldA->SetSeed(seed);
        this->fieldB->SetSeed(seed);
    }
    void FieldProduct3::SetSeed(std::string seed)
    {
        this->fieldA->SetSeed(seed);
        this->fieldB->SetSeed(seed);
    }
}
