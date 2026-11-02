#include "AFunction.h"

namespace Planeted
{
    AFunction::AFunction(const std::string &name, const std::vector<PLTypeInfo*> &argumentTypes)
        : name(name), argumentTypes(argumentTypes)
    { }

    bool AFunction::Matches(const PDSL_Runtime &runtime, const std::vector<Value> &arguments) const
    {
        return true;
    }
}
