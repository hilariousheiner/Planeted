#ifndef PLANETED_FIELDSMODULE_H
#define PLANETED_FIELDSMODULE_H

#include "PLTypeInfo.h"

namespace Planeted
{
    struct PDSL_Runtime;

    class FieldsModule
    {
    public:
        FieldsModule(PDSL_Runtime &runtime);

        PLTypeInfo *GetFBMParametersTypeInfo() const;

        PLTypeInfo *GetFieldTypeInfo() const;
        PLTypeInfo *GetField1TypeInfo() const;
        PLTypeInfo *GetField2TypeInfo() const;

        PLTypeInfo *GetWhiteNoise1TypeInfo() const;
        PLTypeInfo *GetWhiteNoise2TypeInfo() const;
    private:
        PLTypeInfo *fbmParametersTypeInfo;

        PLTypeInfo *fieldTypeInfo;
        PLTypeInfo *field1TypeInfo;
        PLTypeInfo *field2TypeInfo;

        PLTypeInfo *whiteNoise1TypeInfo;
        PLTypeInfo *whiteNoise2TypeInfo;
    };
}
#endif // PLANETED_FIELDSMODULE_H
