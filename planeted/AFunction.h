#ifndef PLANETED_AFUNCTION_H
#define PLANETED_AFUNCTION_H

#include <string>
#include "PDSL_Value.h"
#include "PLTypeInfo.h"

namespace Planeted
{
    struct PDSL_Runtime;

    class AFunction
    {
    public:
        AFunction(const std::string &name, const std::vector<PLTypeInfo*> &argumentTypes);
        virtual ~AFunction() = default;

        virtual Value Call(PDSL_Runtime &runtime, const std::vector<Value>& arguments) const = 0;

    private:
        std::string name;
        std::vector<PLTypeInfo*> argumentTypes;
    };
}
#endif // PLANETED_AFUNCTION_H
