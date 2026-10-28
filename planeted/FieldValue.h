#ifndef PLANETED_FIELDVALUE_H
#define PLANETED_FIELDVALUE_H

#include "Field.h"

namespace Planeted
{
    class Field1Value
    {
    public:
        Field1Value() = default;

        explicit Field1Value(std::unique_ptr<IField1> field)
            : field(std::move(field))
        {}

        Field1Value(const Field1Value &other)
            : noise(other.field->Clone())
        {}

        Field1Value &operator=(const Field1Value &other)
        {
            if(this != &other)
            {
                this->field = other.field->Clone();
            }
            return *this;
        }

        Field1Value(Field1Value&&) noexcept = default;
        Field1Value& operator=(Field1Value&&) noexcept = default;

        IField1 &Get()
        {
            return *(this->field);
        }

    private:
        std::unique_ptr<ANoise> noise;
    };
}
#endif // PLANETED_FIELDVALUE_H
