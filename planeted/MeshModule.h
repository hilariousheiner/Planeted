#ifndef PLANETED_MESHMODULE_H
#define PLANETED_MESHMODULE_H

#include "PLTypeInfo.h"

namespace Planeted
{
    struct PDSL_Runtime;

    class MeshModule
    {
    public:
        MeshModule(PDSL_Runtime &runtime);

        PLTypeInfo *GetMeshTypeInfo() const;

    private:
        PLTypeInfo *meshTypeInfo;
    };
}
#endif
