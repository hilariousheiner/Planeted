#ifndef PLANETED_PLTYPEUTILS_H
#define PLANETED_PLTYPEUTILS_H

#include <string>
#include <vector>

#include "PDSL.h"
#include "PLTypeInfo.h"

namespace Planeted
{
    namespace PLTypeUtils
    {
        std::vector<PLTypeInfo*> ResolveTypes(PDSL_Runtime &runtime, const std::vector<Value> &valueList);

        std::string TypeInfoListToString(const std::vector<PLTypeInfo*> &typeInfoList);
    }
}
#endif // PLANETED_PLTYPEUTILS_H
