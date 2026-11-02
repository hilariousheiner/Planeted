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
    };
}
#endif // PLANETED_BUILTINFUNCION_H
