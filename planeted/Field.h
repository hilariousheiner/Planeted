#ifndef PLANETED_FIELD_H
#define PLANETED_FIELD_H

#include <memory>

#include "FBM.h"
#include "ISeedable.h"
#include "Seed.h"
#include "Vector2.h"
#include "Vector3.h"
#include "PLTypeInfo.h"

namespace Planeted
{
    struct PDSL_Runtime;

    class AField : public ISeedable
    {
    public:
        virtual ~AField() = default;
        virtual std::unique_ptr<AField> Clone() const = 0;

        virtual PLTypeInfo* GetTypeInfo(const PDSL_Runtime &runtime) const;
    };

    class AField1 : public AField
    {
    public:
        virtual ~AField1() = default;
        virtual std::unique_ptr<AField> Clone() const = 0;
        virtual std::unique_ptr<AField1> Clone1() const = 0;

        PLTypeInfo* GetTypeInfo(const PDSL_Runtime &runtime) const override;

        virtual float Eval(const float &p) const = 0;
    };

    class AField2 : public AField
    {
    public:
        virtual ~AField2() = default;
        virtual std::unique_ptr<AField> Clone() const = 0;
        virtual std::unique_ptr<AField2> Clone2() const = 0;

        PLTypeInfo* GetTypeInfo(const PDSL_Runtime &runtime) const override;

        virtual float Eval(const Vector2 &p) const = 0;
    };

    class AField3 : public AField
    {
    public:
        virtual ~AField3() = default;
        virtual std::unique_ptr<AField> Clone() const = 0;
        virtual std::unique_ptr<AField3> Clone3() const = 0;

        PLTypeInfo* GetTypeInfo(const PDSL_Runtime &runtime) const override;

        virtual float Eval(const Vector3 &p) const = 0;
    };

    class AFieldGenerator1 : public AField1
    {
    public:
        void SetSeed(std::uint32_t seedValue) override;
        void SetSeed(std::string seedValue) override;

    protected:
        Seed seed;
    };

    class AFieldGenerator2 : public AField2
    {
    public:
        void SetSeed(std::uint32_t seedValue) override;
        void SetSeed(std::string seedValue) override;

    protected:
        Seed seed;
    };

    class AFieldGenerator3 : public AField3
    {
    public:
        void SetSeed(std::uint32_t seedValue) override;
        void SetSeed(std::string seedValue) override;

    protected:
        Seed seed;
    };

    class ConstantField1 : public AFieldGenerator1
    {
    public:
        ConstantField1(float constant);

        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField1> Clone1() const override;

        float Eval(const float &p) const override;

    private:
        float constant;
    };

    class RidgeFieldModifier1 : public AField1
    {
    public:
        RidgeFieldModifier1(std::unique_ptr<AField1> field);
        RidgeFieldModifier1(const RidgeFieldModifier1 &other);

        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField1> Clone1() const override;

        float Eval(const float &p) const override;

        void SetSeed(std::uint32_t seed) override;
        void SetSeed(std::string seed) override;

    private:
        std::unique_ptr<AField1> field;
    };

    class RidgeFieldModifier2 : public AField2
    {
    public:
        RidgeFieldModifier2(std::unique_ptr<AField2> field);
        RidgeFieldModifier2(const RidgeFieldModifier2 &other);

        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField2> Clone2() const override;

        float Eval(const Vector2 &p) const override;

        void SetSeed(std::uint32_t seed) override;
        void SetSeed(std::string seed) override;

    private:
        std::unique_ptr<AField2> field;
    };

    class AbsFieldModifier1 : public AField1
    {
    public:
        AbsFieldModifier1(std::unique_ptr<AField1> field);
        AbsFieldModifier1(const AbsFieldModifier1 &other);

        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField1> Clone1() const override;

        float Eval(const float &p) const override;

        void SetSeed(std::uint32_t seed) override;
        void SetSeed(std::string seed) override;

    private:
        std::unique_ptr<AField1> field;
    };

    class AbsFieldModifier2 : public AField2
    {
    public:
        AbsFieldModifier2(std::unique_ptr<AField2> field);
        AbsFieldModifier2(const AbsFieldModifier2 &other);

        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField2> Clone2() const override;

        float Eval(const Vector2 &p) const override;

        void SetSeed(std::uint32_t seed) override;
        void SetSeed(std::string seed) override;

    private:
        std::unique_ptr<AField2> field;
    };

    class PowFieldModifier1 : public AField1
    {
    public:
        PowFieldModifier1(std::unique_ptr<AField1> field, float exponent);
        PowFieldModifier1(const PowFieldModifier1 &other);

        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField1> Clone1() const override;

        float Eval(const float &p) const override;

        void SetSeed(std::uint32_t seed) override;
        void SetSeed(std::string seed) override;

    private:
        std::unique_ptr<AField1> field;
        float exponent;
    };

    class PowFieldModifier2 : public AField2
    {
    public:
        PowFieldModifier2(std::unique_ptr<AField2> field, float exponent);
        PowFieldModifier2(const PowFieldModifier2 &other);

        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField2> Clone2() const override;

        float Eval(const Vector2 &p) const override;

        void SetSeed(std::uint32_t seed) override;
        void SetSeed(std::string seed) override;

    private:
        std::unique_ptr<AField2> field;
        float exponent;
    };

    class FBMFieldModifier1 : public AField1
    {
    public:
        FBMFieldModifier1(std::unique_ptr<AField1> field, const FBMParameters &fbmParameters);
        FBMFieldModifier1(const FBMFieldModifier1 &other);

        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField1> Clone1() const override;

        float Eval(const float &p) const override;

        void SetSeed(std::uint32_t seed) override;
        void SetSeed(std::string seed) override;

    private:
        std::unique_ptr<AField1> field;
        FBMParameters fbmParams;
    };

    class FBMFieldModifier2 : public AField2
    {
    public:
        FBMFieldModifier2(std::unique_ptr<AField2> field, const FBMParameters &fbmParameters);
        FBMFieldModifier2(const FBMFieldModifier2 &other);

        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField2> Clone2() const override;

        float Eval(const Vector2 &p) const override;

        void SetSeed(std::uint32_t seed) override;
        void SetSeed(std::string seed) override;

    private:
        std::unique_ptr<AField2> field;
        FBMParameters fbmParams;
    };
}
#endif // PLANETED_FIELD_H
