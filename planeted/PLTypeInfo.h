#ifndef PLANETED_PLTYPEINFO_H
#define PLANETED_PLTYPEINFO_H

#include <string>

#include "ValueTypeEnum.h"

namespace Planeted
{
    class PLTypeInfo
    {
    public:
        PLTypeInfo(const std::string &name, ValueTypeEnum valueType, PLTypeInfo* baseType);

        const std::string &GetName() const;
        ValueTypeEnum GetValueType() const;

        std::string ToString() const;

    private:
        std::string name;
        ValueTypeEnum valueType;
    };
}
#endif // PLANETED_PLTYPEINFO_H
