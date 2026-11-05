#include "PLTypeUtils.h"
#include "Utils.h"

namespace Planeted
{
    namespace PLTypeUtils
    {
        std::vector<PLTypeInfo*> ResolveTypes(PDSL_Runtime &runtime, const std::vector<Value> &valueList)
        {
            std::vector<PLTypeInfo*> result;

            for(size_t i = 0; i < valueList.size(); i++)
            {
                result.push_back(runtime.GetTypeInfo(valueList[i]));
            }
            return result;
        }

        std::string TypeInfoListToString(const std::vector<PLTypeInfo*> &typeInfoList)
        {
            return listToString(typeInfoList,
                                std::function<std::string(PLTypeInfo* const&)>([](PLTypeInfo* typeInfo) { return typeInfo->ToString(); }));
        }
    }
}
