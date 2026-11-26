#include "OperatorsModule.h"

#include "PDSL.h"

namespace Planeted
{
    OperatorsModule::OperatorsModule(PDSL_Runtime &runtime)
        : runtime(runtime)
    {

    }

    static std::string getUnaryOperatorName(TokenTypeEnum op)
    {
        switch(op)
        {
        case TokenTypeEnum::Minus:
            return "negate";
            break;
        default:
            throw std::runtime_error("unknown unary operator");
            break;
        }
    }

    Value OperatorsModule::UnaryOperator(TokenTypeEnum op, const Value &operand)
    {
        std::string name = getUnaryOperatorName(op);

        std::vector<Value> args { operand };
        return this->runtime.CallFunction(name, args);
    }
}

