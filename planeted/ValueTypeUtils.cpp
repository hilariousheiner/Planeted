#include "ValueTypeUtils.h"

namespace Planeted
{
    namespace ValueTypeUtils
    {
        std::string ValueTypeToString(ValueTypeEnum valueType)
        {
            std::string result = "";

            switch(valueType)
            {
            case ValueTypeEnum::Int:
                result = "Int";
                break;
            case ValueTypeEnum::Float:
                result = "Float";
                break;
            case ValueTypeEnum::Bool:
                result = "Bool";
                break;
            case ValueTypeEnum::String:
                result = "String";
                break;
            case ValueTypeEnum::Null:
                result = "Null";
                break;
            case ValueTypeEnum::Tuple:
                result = "Tuple";
                break;
            case ValueTypeEnum::List:
                result = "List";
                break;
            case ValueTypeEnum::Mesh:
                result = "Mesh";
                break;
            case ValueTypeEnum::Noise:
                result = "Noise";
                break;
            case ValueTypeEnum::Field:
                result = "Field";
                break;
            case ValueTypeEnum::FBMParameters:
                result = "FBMParameters";
                break;
            default:
                break;
            }
            return result;
        }
    }
}
