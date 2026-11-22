#include "MeshModule.h"
#include "PDSL.h"
#include "PDSL_Utils.h"

namespace Planeted
{
    static DisplacementFunction fieldDisplaceFun(const AField3 &field3)
    {
        return [&field3](const Vector3 &v)
        {
            return field3.Eval(v);
        };
    }
    static Value builtin_displaceNormal(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        Mesh m = GetMeshArg(args, 0, "displace");
        FieldValue fieldValue = GetFieldArg(args, 1, "displace");
        float a = GetFloatArg(args, 2, "displace");

        AField3 &field3 = dynamic_cast<AField3&>(fieldValue.Get());

        m.Displace(fieldDisplaceFun(field3), a, DisplacementTypeEnum::Normal);
        return Value(m);
    }

    MeshModule::MeshModule(PDSL_Runtime &runtime)
    {
        PLTypeInfo *meshTypeInfo = runtime.GetMeshTypeInfo();
        PLTypeInfo *floatTypeInfo = runtime.GetFloatTypeInfo();
        PLTypeInfo *field3TypeInfo = runtime.FieldsMod->GetField3TypeInfo();

        runtime.DefineFunction("displace", {meshTypeInfo, field3TypeInfo, floatTypeInfo}, builtin_displaceNormal);
    }
}
