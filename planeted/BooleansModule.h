#ifndef PLANETED_BOOLEANSMODULE_H
#define PLANETED_BOOLEANSMODULE_H

#include "PLTypeInfo.h"

namespace Planeted
{
    struct PDSL_Runtime;

    class BooleansModule
    {
    public:
        BooleansModule(PDSL_Runtime &runtime);

        PLTypeInfo *GetBooleanTypeInfo() const;

    private:
        PLTypeInfo *booleanTypeInfo;
    };
}
#endif // PLANETED_BOOLEANSMODULE_H
