#include "FieldsModule.h"
#include "PDSL.h"

namespace Planeted
{
	FieldsModule::FieldsModule(PDSL_Runtime &runtime)
    {
        this->fbmParametersTypeInfo = runtime.DefineType("FBMParamters", ValueTypeEnum::FBMParameters, nullptr);

        this->fieldTypeInfo = runtime.DefineType("Field", ValueTypeEnum::Field, nullptr);
        this->field1TypeInfo = runtime.DefineType("Field1", ValueTypeEnum::Field, this->fieldTypeInfo);
    }

    PLTypeInfo *FieldsModule::GetFBMParametersTypeInfo() const
    {
        return this->fbmParametersTypeInfo;
    }

    PLTypeInfo *FieldsModule::GetFieldTypeInfo() const
    {
        return this->fieldTypeInfo;
    }
    PLTypeInfo *FieldsModule::GetField1TypeInfo() const
    {
        return this->field1TypeInfo;
    }
}
