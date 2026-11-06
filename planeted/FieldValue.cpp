#include "FieldValue.h"
#include "PDSL.h"

namespace Planeted
{
    FieldValue::FieldValue(std::unique_ptr<IField> field)
        : field(std::move(field))
    {}

    FieldValue::FieldValue(const FieldValue &other)
        : field(other.field->Clone())
    {}

    FieldValue &FieldValue::operator=(const FieldValue &other)
    {
        if(this != &other)
        {
            this->field = other.field->Clone();
        }
        return *this;
    }

    IField &FieldValue::Get()
    {
        return *(this->field);
    }

    PLTypeInfo* FieldValue::GetTypeInfo(const PDSL_Runtime &runtime) const
    {
        return runtime.GetFieldTypeInfo();
    }
}
