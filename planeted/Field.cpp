#include "Field.h"
#include "PDSL.h"

namespace Planeted
{
    PLTypeInfo* AField::GetTypeInfo(const PDSL_Runtime &runtime) const
    {
        return runtime.FieldsMod->GetFieldTypeInfo();
    }

    PLTypeInfo* AField1::GetTypeInfo(const PDSL_Runtime &runtime) const
    {
        return runtime.FieldsMod->GetField1TypeInfo();
    }

    PLTypeInfo* AField2::GetTypeInfo(const PDSL_Runtime &runtime) const
    {
        return runtime.FieldsMod->GetField2TypeInfo();
    }

    PLTypeInfo* AField3::GetTypeInfo(const PDSL_Runtime &runtime) const
    {
        return runtime.FieldsMod->GetField3TypeInfo();
    }

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

    std::unique_ptr<AField> ConstantField1::Clone() const
    {
        return std::make_unique<ConstantField1>(*this);
    }
    std::unique_ptr<AField1> ConstantField1::Clone1() const
    {
        return std::make_unique<ConstantField1>(*this);
    }

    float ConstantField1::Eval(const float &p) const
    {
        return this->constant;
    }

    //------------------------------------------------
    RidgeFieldModifier1::RidgeFieldModifier1(std::unique_ptr<AField1> field)
        : field(std::move(field))
    {}

    RidgeFieldModifier1::RidgeFieldModifier1(const RidgeFieldModifier1 &other)
        : AField1(other), field(other.field->Clone1())
    {}

    std::unique_ptr<AField> RidgeFieldModifier1::Clone() const
    {
        return std::make_unique<RidgeFieldModifier1>(*this);
    }
    std::unique_ptr<AField1> RidgeFieldModifier1::Clone1() const
    {
        return std::make_unique<RidgeFieldModifier1>(*this);
    }

    float RidgeFieldModifier1::Eval(const float &p) const
    {
        float n = (0.9f - std::abs(this->field->Eval(p)));
        return n*n;
    }

    void RidgeFieldModifier1::SetSeed(std::uint32_t seed)
    {
        this->field->SetSeed(seed);
    }
    void RidgeFieldModifier1::SetSeed(std::string seed)
    {
        this->field->SetSeed(seed);
    }
    //---------------------
    RidgeFieldModifier2::RidgeFieldModifier2(std::unique_ptr<AField2> field)
        : field(std::move(field))
    {}

    RidgeFieldModifier2::RidgeFieldModifier2(const RidgeFieldModifier2 &other)
        : AField2(other), field(other.field->Clone2())
    {}

    std::unique_ptr<AField> RidgeFieldModifier2::Clone() const
    {
        return std::make_unique<RidgeFieldModifier2>(*this);
    }
    std::unique_ptr<AField2> RidgeFieldModifier2::Clone2() const
    {
        return std::make_unique<RidgeFieldModifier2>(*this);
    }

    float RidgeFieldModifier2::Eval(const Vector2 &p) const
    {
        float n = (0.9f - std::abs(this->field->Eval(p)));
        return n*n;
    }

    void RidgeFieldModifier2::SetSeed(std::uint32_t seed)
    {
        this->field->SetSeed(seed);
    }
    void RidgeFieldModifier2::SetSeed(std::string seed)
    {
        this->field->SetSeed(seed);
    }
    //-----------------------------------------

    RidgeFieldModifier3::RidgeFieldModifier3(std::unique_ptr<AField3> field)
        : field(std::move(field))
    {}

    RidgeFieldModifier3::RidgeFieldModifier3(const RidgeFieldModifier3 &other)
        : AField3(other), field(other.field->Clone3())
    {}

    std::unique_ptr<AField> RidgeFieldModifier3::Clone() const
    {
        return std::make_unique<RidgeFieldModifier3>(*this);
    }
    std::unique_ptr<AField3> RidgeFieldModifier3::Clone3() const
    {
        return std::make_unique<RidgeFieldModifier3>(*this);
    }

    float RidgeFieldModifier3::Eval(const Vector3 &p) const
    {
        float n = (0.9f - std::abs(this->field->Eval(p)));
        return n*n;
    }

    void RidgeFieldModifier3::SetSeed(std::uint32_t seed)
    {
        this->field->SetSeed(seed);
    }
    void RidgeFieldModifier3::SetSeed(std::string seed)
    {
        this->field->SetSeed(seed);
    }

    //----------------------
    AbsFieldModifier1::AbsFieldModifier1(std::unique_ptr<AField1> field)
        : field(std::move(field))
    {}

    AbsFieldModifier1::AbsFieldModifier1(const AbsFieldModifier1 &other)
        : AField1(other), field(other.field->Clone1())
    {}

    std::unique_ptr<AField> AbsFieldModifier1::Clone() const
    {
        return std::make_unique<AbsFieldModifier1>(*this);
    }
    std::unique_ptr<AField1> AbsFieldModifier1::Clone1() const
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
    //-------------------------------------------------------------------

    AbsFieldModifier2::AbsFieldModifier2(std::unique_ptr<AField2> field)
        : field(std::move(field))
    {}

    AbsFieldModifier2::AbsFieldModifier2(const AbsFieldModifier2 &other)
        : AField2(other), field(other.field->Clone2())
    {}

    std::unique_ptr<AField> AbsFieldModifier2::Clone() const
    {
        return std::make_unique<AbsFieldModifier2>(*this);
    }
    std::unique_ptr<AField2> AbsFieldModifier2::Clone2() const
    {
        return std::make_unique<AbsFieldModifier2>(*this);
    }

    float AbsFieldModifier2::Eval(const Vector2 &p) const
    {
        return std::abs(this->field->Eval(p));
    }

    void AbsFieldModifier2::SetSeed(std::uint32_t seed)
    {
        this->field->SetSeed(seed);
    }
    void AbsFieldModifier2::SetSeed(std::string seed)
    {
        this->field->SetSeed(seed);
    }
    // --------------------------------------------

    AbsFieldModifier3::AbsFieldModifier3(std::unique_ptr<AField3> field)
        : field(std::move(field))
    {}

    AbsFieldModifier3::AbsFieldModifier3(const AbsFieldModifier3 &other)
        : AField3(other), field(other.field->Clone3())
    {}

    std::unique_ptr<AField> AbsFieldModifier3::Clone() const
    {
        return std::make_unique<AbsFieldModifier3>(*this);
    }
    std::unique_ptr<AField3> AbsFieldModifier3::Clone3() const
    {
        return std::make_unique<AbsFieldModifier3>(*this);
    }

    float AbsFieldModifier3::Eval(const Vector3 &p) const
    {
        return std::abs(this->field->Eval(p));
    }

    void AbsFieldModifier3::SetSeed(std::uint32_t seed)
    {
        this->field->SetSeed(seed);
    }
    void AbsFieldModifier3::SetSeed(std::string seed)
    {
        this->field->SetSeed(seed);
    }

    // ---------------------------------------------------------------------
    PowFieldModifier1::PowFieldModifier1(std::unique_ptr<AField1> field, float exponent)
        : field(std::move(field)), exponent(exponent)
    {}

    PowFieldModifier1::PowFieldModifier1(const PowFieldModifier1 &other)
        : AField1(other), field(other.field->Clone1()), exponent(other.exponent)
    {}

    std::unique_ptr<AField> PowFieldModifier1::Clone() const
    {
        return std::make_unique<PowFieldModifier1>(*this);
    }
    std::unique_ptr<AField1> PowFieldModifier1::Clone1() const
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
    //----------------------------------------
    PowFieldModifier2::PowFieldModifier2(std::unique_ptr<AField2> field, float exponent)
        : field(std::move(field)), exponent(exponent)
    {}

    PowFieldModifier2::PowFieldModifier2(const PowFieldModifier2 &other)
        : AField2(other), field(other.field->Clone2()), exponent(other.exponent)
    {}

    std::unique_ptr<AField> PowFieldModifier2::Clone() const
    {
        return std::make_unique<PowFieldModifier2>(*this);
    }
    std::unique_ptr<AField2> PowFieldModifier2::Clone2() const
    {
        return std::make_unique<PowFieldModifier2>(*this);
    }

    float PowFieldModifier2::Eval(const Vector2 &p) const
    {
        return std::pow(this->field->Eval(p), this->exponent);
    }

    void PowFieldModifier2::SetSeed(std::uint32_t seed)
    {
        this->field->SetSeed(seed);
    }
    void PowFieldModifier2::SetSeed(std::string seed)
    {
        this->field->SetSeed(seed);
    }
    //----------------------------------------

    FBMFieldModifier1::FBMFieldModifier1(std::unique_ptr<AField1> field, const FBMParameters &fbmParameters)
        : field(std::move(field)), fbmParams(fbmParameters)
    { }

    FBMFieldModifier1::FBMFieldModifier1(const FBMFieldModifier1 &other)
        : AField1(other), field(other.field->Clone1()), fbmParams(other.fbmParams)
    { }


    std::unique_ptr<AField> FBMFieldModifier1::Clone() const
    {
        return std::make_unique<FBMFieldModifier1>(*this);
    }
    std::unique_ptr<AField1> FBMFieldModifier1::Clone1() const
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

    // ------------------------------------------------------

    FBMFieldModifier2::FBMFieldModifier2(std::unique_ptr<AField2> field, const FBMParameters &fbmParameters)
        : field(std::move(field)), fbmParams(fbmParameters)
    { }

    FBMFieldModifier2::FBMFieldModifier2(const FBMFieldModifier2 &other)
        : AField2(other), field(other.field->Clone2()), fbmParams(other.fbmParams)
    { }


    std::unique_ptr<AField> FBMFieldModifier2::Clone() const
    {
        return std::make_unique<FBMFieldModifier2>(*this);
    }
    std::unique_ptr<AField2> FBMFieldModifier2::Clone2() const
    {
        return std::make_unique<FBMFieldModifier2>(*this);
    }

    float FBMFieldModifier2::Eval(const Vector2 &p) const
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

    void FBMFieldModifier2::SetSeed(std::uint32_t seed)
    {
        this->field->SetSeed(seed);
    }
    void FBMFieldModifier2::SetSeed(std::string seed)
    {
        this->field->SetSeed(seed);
    }
}
