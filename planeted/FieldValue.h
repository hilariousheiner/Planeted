#ifndef PLANETED_FIELDVALUE_H
#define PLANETED_FIELDVALUE_H

#include "Field.h"

namespace Planeted
{
    class FieldValue
    {
    public:
        FieldValue() = default;

        explicit FieldValue(std::unique_ptr<IField> field)
            : field(std::move(field))
        {}

        FieldValue(const FieldValue &other)
            : field(other.field->Clone())
        {}

        FieldValue &operator=(const FieldValue &other)
        {
            if(this != &other)
            {
                this->field = other.field->Clone();
            }
            return *this;
        }

        FieldValue(FieldValue&&) noexcept = default;
        FieldValue& operator=(FieldValue&&) noexcept = default;

        IField &Get()
        {
            return *(this->field);
        }

    private:
        std::unique_ptr<IField> field;
    };
}
#endif // PLANETED_FIELDVALUE_H
