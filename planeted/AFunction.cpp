#include "AFunction.h"

namespace Planeted
{
    AFunction::AFunction(const std::string &name, const std::vector<PLTypeInfo*> &argumentTypes)
        : name(name), argumentTypes(argumentTypes)
    { }
}
