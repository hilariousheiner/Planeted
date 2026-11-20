#include "PDSL_Lib.h"

#include <memory>
#include <iostream>

#include "Math.h"
#include "Noise.h"
#include "PerlinNoise.h"
#include "PDSL_Utils.h"
#include "Tests.h"
#include "PGM.h"
#include "PixelMap.h"
#include "ValueNoise.h"
#include "WhiteNoise.h"

namespace Planeted
{
    namespace PDSL_Lib
    {
        static DisplacementTypeEnum toDisplacementType(int type)
        {
            DisplacementTypeEnum result = DisplacementTypeEnum::Vertex;

            switch(type)
            {
            case 0:
                result = DisplacementTypeEnum::Vertex;
                break;
            case 1:
                result = DisplacementTypeEnum::Normal;
                break;
            default:
                break;
            }
            return result;
        }

        static Value builtin_whiteNoise(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCountAtMost(args, 1, "whiteNoise");

            NoiseValue noiseValue(std::make_unique<WhiteNoise>());

            if(args.size() == 1)
            {
                SetSeed(noiseValue.Get(), args[0]);
            }
            return Value(noiseValue);
        }
        static Value builtin_valueNoise(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCountAtMost(args, 1, "valueNoise");

            NoiseValue noiseValue(std::make_unique<ValueNoise>());

            if(args.size() == 1)
            {
                SetSeed(noiseValue.Get(), args[0]);
            }
            return Value(noiseValue);
        }
        static Value builtin_perlinNoise(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCountAtMost(args, 1, "perlinNoise");
            NoiseValue noiseValue(std::make_unique<PerlinNoise>());

            if(args.size() == 1)
            {
                SetSeed(noiseValue.Get(), args[0]);
            }
            return Value(noiseValue);
        }

        static Value builtin_ridge(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "ridge");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "ridge");

            NoiseValue ridgedNoiseValue(RidgeNoiseModifier(noiseValue.Get().Clone()).Clone());
            return Value(ridgedNoiseValue);
        }
        static Value builtin_fbm(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "fbm");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "fbm");
            FBMParameters parametersValue = GetFBMParametersArg(args, 1, "fbm");

            NoiseValue fbmNoiseValue(FBMNoiseModifier(noiseValue.Get().Clone(), parametersValue).Clone());

            return Value(fbmNoiseValue);
        }

        static Value builtin_abs(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "abs");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "abs");

            NoiseValue absNoiseValue(AbsNoiseModifier(noiseValue.Get().Clone()).Clone());
            return Value(absNoiseValue);
        }
        static Value builtin_pow(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "pow");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "pow");
            float exponent = GetFloatArg(args, 1, "pow");

            NoiseValue powNoiseValue(PowNoiseModifier(noiseValue.Get().Clone(), exponent).Clone());
            return Value(powNoiseValue);
        }

        static Value builtin_setWhiteNoiseScale(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setWhiteNoiseScale");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "setWhiteNoiseScale");

            WhiteNoise &wNoise = dynamic_cast<WhiteNoise&>(noiseValue.Get());
            wNoise.SetWhiteNoiseScale(GetFloatArg(args, 1, "setWhiteNoiseScale"));
            return Value(NoiseValue(wNoise.Clone()));
        }

        static Value builtin_subdivide(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "subdivide");

            Mesh m = GetMeshArg(args, 0, "subdivide");
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

        static DisplacementFunction noiseDisplaceFun(const ANoise &noise)
        {
            return [&noise](const Vector3 &v)
            {
                return noise.Eval(v);
            };
        }

        static Value builtin_displaceNoise(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            Mesh m = GetMeshArg(args, 0, "displace");
            NoiseValue noiseValue = GetNoiseArg(args, 1, "displace");
            float a = GetFloatArg(args, 2, "displace");

            //DisplacementTypeEnum displacementType = toDisplacementType(args[3].GetIntValue());
            DisplacementTypeEnum displacementType = toDisplacementType(GetIntArg(args, 3, "displace"));

            m.Displace(noiseDisplaceFun(noiseValue.Get()), a, displacementType);
            return Value(m);
        }

        static Value builtin_displaceNoiseNormal(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            Mesh m = GetMeshArg(args, 0, "displace");
            NoiseValue noiseValue = GetNoiseArg(args, 1, "displace");
            float a = GetFloatArg(args, 2, "displace");

            m.Displace(noiseDisplaceFun(noiseValue.Get()), a, DisplacementTypeEnum::Normal);
            return Value(m);
        }

        void Load(PDSL_Runtime &runtime)
        {
            PLTypeInfo *noiseTypeInfo = runtime.GetNoiseTypeInfo();
            PLTypeInfo *fbmParametersTypeInfo = runtime.FieldsMod->GetFBMParametersTypeInfo();
            PLTypeInfo *floatTypeInfo = runtime.GetFloatTypeInfo();
            PLTypeInfo *meshTypeInfo = runtime.GetMeshTypeInfo();
            PLTypeInfo *intTypeInfo = runtime.GetIntegerTypeInfo();

            runtime.DefineIntrinsicFunction("whiteNoise", builtin_whiteNoise);
            runtime.DefineIntrinsicFunction("valueNoise", builtin_valueNoise);
            runtime.DefineIntrinsicFunction("perlinNoise", builtin_perlinNoise);

            runtime.DefineFunction("ridge", {noiseTypeInfo}, builtin_ridge);
            runtime.DefineFunction("fbm", {noiseTypeInfo, fbmParametersTypeInfo}, builtin_fbm);

            runtime.DefineFunction("abs", {noiseTypeInfo}, builtin_abs);
            runtime.DefineFunction("pow", {noiseTypeInfo, floatTypeInfo}, builtin_pow);

            runtime.DefineFunction("setWhiteNoiseScale", {noiseTypeInfo, floatTypeInfo}, builtin_setWhiteNoiseScale);

            runtime.DefineIntrinsicFunction("subdivide", builtin_subdivide);
            runtime.DefineIntrinsicFunction("tessellate", builtin_tessellate);
            runtime.DefineIntrinsicFunction("projectToUnitSphere", builtin_projectToUnitSphere);
            runtime.DefineIntrinsicFunction("calculateNormals", builtin_calculateNormals);

            runtime.DefineFunction("displace", {meshTypeInfo, noiseTypeInfo, floatTypeInfo, intTypeInfo}, builtin_displaceNoise);
            runtime.DefineFunction("displace", {meshTypeInfo, noiseTypeInfo, floatTypeInfo}, builtin_displaceNoiseNormal);
        }
    }
}
