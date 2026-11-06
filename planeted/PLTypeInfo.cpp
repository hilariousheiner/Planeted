#include "PLTypeInfo.h"

#include "ValueTypeUtils.h"

namespace Planeted
{
    PLTypeInfo::PLTypeInfo(const std::string &name, ValueTypeEnum valueType, PLTypeInfo* baseType)
        : name(name), valueType(valueType), baseTypeInfo(baseType)
    {}

    const std::string &PLTypeInfo::GetName() const
    {
        return this->name;
    }
    ValueTypeEnum PLTypeInfo::GetValueType() const
    {
        return this->valueType;
    }

    bool PLTypeInfo::IsDerivedFrom(const PLTypeInfo *other) const
    {
        if(other == nullptr)
        {
            return false;
        }

        if(this == other)
        {
            return true;
        }

        if(this->baseTypeInfo == nullptr)
        {
            return false;
        }
        return this->baseTypeInfo->IsDerivedFrom(other);
    }

    std::string PLTypeInfo::ToString() const
    {
        return this->GetName() + "/" + ValueTypeUtils::ValueTypeToString(this->GetValueType());
    }
}
