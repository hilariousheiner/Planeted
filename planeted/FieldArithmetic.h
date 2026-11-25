#ifndef PLANETED_FIELDARITHMETIC_H
#define PLANETED_FIELDARITHMETIC_H

#include "Field.h"

namespace Planeted
{
    class FieldSum1 : public AField1
    {
    public:
        FieldSum1(std::unique_ptr<AField1> fieldA, std::unique_ptr<AField1> fieldB);
        FieldSum1(const FieldSum1 &other);

        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField1> Clone1() const override;

        float Eval(const float &p) const override;

        void SetSeed(std::uint32_t seed) override;
        void SetSeed(std::string seed) override;

    private:
        std::unique_ptr<AField1> fieldA;
        std::unique_ptr<AField1> fieldB;
    };

    class FieldSum2 : public AField2
    {
    public:
        FieldSum2(std::unique_ptr<AField2> fieldA, std::unique_ptr<AField2> fieldB);
        FieldSum2(const FieldSum2 &other);

        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField2> Clone2() const override;

        float Eval(const Vector2 &p) const override;

        void SetSeed(std::uint32_t seed) override;
        void SetSeed(std::string seed) override;

    private:
        std::unique_ptr<AField2> fieldA;
        std::unique_ptr<AField2> fieldB;
    };

    class FieldSum3 : public AField3
    {
    public:
        FieldSum3(std::unique_ptr<AField3> fieldA, std::unique_ptr<AField3> fieldB);
        FieldSum3(const FieldSum3 &other);

        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField3> Clone3() const override;

        float Eval(const Vector3 &p) const override;

        void SetSeed(std::uint32_t seed) override;
        void SetSeed(std::string seed) override;

    private:
        std::unique_ptr<AField3> fieldA;
        std::unique_ptr<AField3> fieldB;
    };


    class FieldProduct1 : public AField1
    {
    public:
        FieldProduct1(std::unique_ptr<AField1> fieldA, std::unique_ptr<AField1> fieldB);
        FieldProduct1(const FieldProduct1 &other);

        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField1> Clone1() const override;

        float Eval(const float &p) const override;

        void SetSeed(std::uint32_t seed) override;
        void SetSeed(std::string seed) override;

    private:
        std::unique_ptr<AField1> fieldA;
        std::unique_ptr<AField1> fieldB;
    };
    class FieldProduct2 : public AField2
    {
    public:
        FieldProduct2(std::unique_ptr<AField2> fieldA, std::unique_ptr<AField2> fieldB);
        FieldProduct2(const FieldProduct2 &other);

        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField2> Clone2() const override;

        float Eval(const Vector2 &p) const override;

        void SetSeed(std::uint32_t seed) override;
        void SetSeed(std::string seed) override;

    private:
        std::unique_ptr<AField2> fieldA;
        std::unique_ptr<AField2> fieldB;
    };
    class FieldProduct3 : public AField3
    {
    public:
        FieldProduct3(std::unique_ptr<AField3> fieldA, std::unique_ptr<AField3> fieldB);
        FieldProduct3(const FieldProduct3 &other);

        std::unique_ptr<AField> Clone() const override;
        std::unique_ptr<AField3> Clone3() const override;

        float Eval(const Vector3 &p) const override;

        void SetSeed(std::uint32_t seed) override;
        void SetSeed(std::string seed) override;

    private:
        std::unique_ptr<AField3> fieldA;
        std::unique_ptr<AField3> fieldB;
    };
}
#endif // PLANETED_FIELDARITHMETIC_H
