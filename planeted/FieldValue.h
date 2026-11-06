#ifndef PLANETED_FIELDVALUE_H
#define PLANETED_FIELDVALUE_H

#include "Field.h"

namespace Planeted
{
    class FieldValue
    {
    public:
        FieldValue() = default;

        explicit FieldValue(std::unique_ptr<IField> field);

        FieldValue(const FieldValue &other);

        FieldValue &operator=(const FieldValue &other);

        FieldValue(FieldValue&&) noexcept = default;
        FieldValue& operator=(FieldValue&&) noexcept = default;

        IField &Get();

    private:
        std::unique_ptr<IField> field;
    };
}
#endif // PLANETED_FIELDVALUE_H
