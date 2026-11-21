#include "IOModule.h"
#include "PDSL.h"
#include "PLTypeInfo.h"

namespace Planeted
{
    IOModule::IOModule(PDSL_Runtime &runtime)
    {
        PLTypeInfo *field1TypeInfo = runtime.FieldsMod->GetField1TypeInfo();
    }
}
