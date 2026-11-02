#include "BuiltinFunction.h"

namespace Planeted
{
    BuiltinFunction::BuiltinFunction(const std::string &name, const std::vector<PLTypeInfo*> &argumentTypes, BuiltinFunction::BuiltinFunctionPtr fn)
        : AFunction(name, argumentTypes), fn(fn)
    {}

    Value BuiltinFunction::Call(PDSL_Runtime &runtime, const std::vector<Value>& arguments) const
    {
        return this->fn(runtime, arguments);
    }
}
