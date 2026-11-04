#include "PLTypeInfo.h"

#include "ValueTypeUtils.h"

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

    std::string PLTypeInfo::ToString() const
    {
        return this->GetName() + "/" + ValueTypeUtils::ValueTypeToString(this->GetValueType());
    }
}
