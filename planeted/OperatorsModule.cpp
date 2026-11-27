#include "OperatorsModule.h"

#include "PDSL.h"

namespace Planeted
{
    OperatorsModule::OperatorsModule(PDSL_Runtime &runtime)
        : runtime(runtime)
    { }

    static std::string getUnaryOperatorName(TokenTypeEnum op)
    {
        switch(op)
        {
        case TokenTypeEnum::Minus:
            return OperatorsModule::NEGATE;
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

    static std::string getBinaryOperatorName(TokenTypeEnum op)
    {
        switch(op)
        {
        case TokenTypeEnum::Star:
            return OperatorsModule::MULTIPLY;
        case TokenTypeEnum::Plus:
            return OperatorsModule::ADD;
            break;
        default:
            throw std::runtime_error("unknown binary operator");
            break;
        }
    }
    Value OperatorsModule::BinaryOperator(TokenTypeEnum op, const Value &left, const Value &right)
    {
        std::string name = getBinaryOperatorName(op);

        std::vector<Value> args { left, right };
        return this->runtime.CallFunction(name, args);
    }
}

