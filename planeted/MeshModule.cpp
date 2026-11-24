#include "MeshModule.h"
#include "PDSL.h"
#include "PDSL_Utils.h"

namespace Planeted
{
    static Value builtin_subdivide(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        Mesh m = GetMeshArg(args, 0, "subdivide");
        int d = GetIntArg(args, 1, "subdivide");

        m.Subdivide(d);

        return Value(m);
    }
    static Value builtin_subdivideTuple(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        Mesh m;
        if(TupleToMesh(args[0].GetTupleValue(), m) == false)
        {
            throw std::runtime_error("subdivide: argument 1 must be a mesh.");
        }

        int d = GetIntArg(args, 1, "subdivide");

        m.Subdivide(d);

        return Value(m);
    }
    static Value builtin_tessellate(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        ExpectArgsCount(args, 2, "tessellate");

        Mesh m = GetMeshArg(args, 0, "tessellate");
        int n = args[1].GetIntValue();

        m.Tessellate(n);

        return Value(m);
    }
    static Value builtin_projectToUnitSphere(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        ExpectArgsCount(args, 1, "projectToUnitSphere");

        Mesh m = GetMeshArg(args, 0, "projectToUnitSphere");
        m.ProjectToUnitSphere();

        return Value(m);
    }
    static Value builtin_calculateNormals(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        ExpectArgsCount(args, 1, "calculateNormals");

        Mesh m = GetMeshArg(args, 0, "calculateNormals");
        m.CalculateNormals();

        return Value(m);
    }

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
        PLTypeInfo *intTypeInfo = runtime.GetIntegerTypeInfo();
        PLTypeInfo *tupleTypeInfo = runtime.GetTupleTypeInfo();
        PLTypeInfo *floatTypeInfo = runtime.GetFloatTypeInfo();
        PLTypeInfo *field3TypeInfo = runtime.FieldsMod->GetField3TypeInfo();

        runtime.DefineFunction("displace", {meshTypeInfo, field3TypeInfo, floatTypeInfo}, builtin_displaceNormal);

        runtime.DefineFunction("subdivide", {meshTypeInfo, intTypeInfo}, builtin_subdivide);
        runtime.DefineFunction("subdivide", {tupleTypeInfo, intTypeInfo}, builtin_subdivideTuple);

        runtime.DefineFunction("tessellate", {meshTypeInfo, intTypeInfo}, builtin_tessellate);
        runtime.DefineFunction("projectToUnitSphere", {meshTypeInfo}, builtin_projectToUnitSphere);
        runtime.DefineFunction("calculateNormals", {meshTypeInfo}, builtin_calculateNormals);
    }
}
