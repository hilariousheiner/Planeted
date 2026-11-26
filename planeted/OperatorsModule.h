#ifndef PLANETED_OPERATORSMODULE_H
#define PLANETED_OPERATORSMODULE_H

#include "PDSL_Token.h"
#include "PDSL_Value.h"

namespace Planeted
{
    struct PDSL_Runtime;

    class OperatorsModule
    {
    public:
        OperatorsModule(PDSL_Runtime &runtime);

        Value UnaryOperator(TokenTypeEnum op, const Value &operand);
    private:
        PDSL_Runtime &runtime;
    };
}
#endif // PLANETED_OPERATORSMODULE_H
