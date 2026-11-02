#ifndef PLANETED_BUILTINFUNCTION_H
#define PLANETED_BUILTINFUNCTION_H

#include "AFunction.h"
#include "PLTypeInfo.h"

namespace Planeted
{
    class BuiltinFunction : public AFunction
    {
    public:
        using BuiltinFunctionPtr = std::function<Value(PDSL_Runtime&, const std::vector<Value>&)>;

        BuiltinFunction(const std::string &name, const std::vector<PLTypeInfo*> &argumentTypes, BuiltinFunction::BuiltinFunctionPtr fn);

        Value Call(PDSL_Runtime &runtime, const std::vector<Value>& arguments) const override;

    private:
        BuiltinFunction::BuiltinFunctionPtr fn;
    };
}
#endif // PLANETED_BUILTINFUNCION_H
