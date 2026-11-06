#include "AFunction.h"
#include "PDSL.h"

namespace Planeted
{
    AFunction::AFunction(const std::string &name, const std::vector<PLTypeInfo*> &argumentTypes)
        : name(name), argumentTypes(argumentTypes)
    { }

    bool AFunction::Matches(const PDSL_Runtime &runtime, const std::vector<Value> &arguments) const
    {
        if (arguments.size() != argumentTypes.size())
        {
            return false;
        }

        for (size_t i = 0; i < arguments.size(); i++)
        {
            PLTypeInfo* argumentType = runtime.GetTypeInfo(arguments[i]);
            PLTypeInfo* parameterType = argumentTypes[i];

            if(!argumentType->IsDerivedFrom(parameterType))
            {
                return false;
            }
        }
        return true;
    }
}
