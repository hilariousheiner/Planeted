#ifndef PLANETED_AFUNCTION_H
#define PLANETED_AFUNCTION_H

#include <string>

#include "PDSL.h"

namespace Planeted
{
    class AFunction
    {
    public:
        AFunction(const std::string &name);

        virtual Value Call(PDSL_Runtime &runtime, const std::vector<Value>& arguments) const = 0;

    private:
        std::string name;
    };
}
#endif // PLANETED_AFUNCTION_H
