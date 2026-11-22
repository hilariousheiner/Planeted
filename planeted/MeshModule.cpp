#include "MeshModule.h"
#include "PDSL.h"

namespace Planeted
{
    MeshModule::MeshModule(PDSL_Runtime &runtime)
    {
        PLTypeInfo *meshTypeInfo = runtime.GetMeshTypeInfo();
    }
}
