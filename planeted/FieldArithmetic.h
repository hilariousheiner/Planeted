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
}
#endif // PLANETED_FIELDARITHMETIC_H
