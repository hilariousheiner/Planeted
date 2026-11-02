#include "PLTypeInfo.h"

namespace Planeted
{
    PLTypeInfo::PLTypeInfo(const std::string &name, ValueTypeEnum valueType, PLTypeInfo* baseType)
        : name(name), valueType(valueType)
    {}

    const std::string &PLTypeInfo::GetName() const
    {
        return this->name;
    }
    ValueTypeEnum PLTypeInfo::GetValueType() const
    {
        return this->valueType;
    }
}
