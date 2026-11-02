#ifndef PLANETED_PLTYPEINFO_H
#define PLANETED_PLTYPEINFO_H

#include <string>

#include "PDSL_Value.h"

namespace Planeted
{
    class PLTypeInfo
    {
    public:
        PLTypeInfo(const std::string &name, ValueTypeEnum valueType, PLTypeInfo* baseType);

        const std::string &GetName() const;
        ValueTypeEnum GetValueType() const;

    private:
        std::string name;
        ValueTypeEnum valueType;
    };
}
#endif // PLANETED_PLTYPEINFO_H
