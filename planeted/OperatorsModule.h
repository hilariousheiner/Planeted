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

        inline static const std::string ADD = "add";
        inline static const std::string SUBTRACT = "sub";
        inline static const std::string MULTIPLY = "mul";
        inline static const std::string DIVIDE = "div";
        inline static const std::string NEGATE = "neg";

    private:
        PDSL_Runtime &runtime;
    };
}
#endif // PLANETED_OPERATORSMODULE_H
