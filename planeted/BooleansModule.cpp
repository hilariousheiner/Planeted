#include "BooleansModule.h"

#include "PDSL.h"

namespace Planeted
{
    BooleansModule::BooleansModule(PDSL_Runtime &runtime)
    {
        this->booleanTypeInfo = runtime.DefineType("Boolean", ValueTypeEnum::Bool, nullptr);
    }

    PLTypeInfo *BooleansModule::GetBooleanTypeInfo() const
    {
        return this->booleanTypeInfo;
    }
}
