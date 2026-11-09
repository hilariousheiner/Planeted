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


        static Value builtin_noiseTest(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "noiseTest");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "noiseTest");
            std::string filename = GetStringArg(args, 1, "noiseTest");

            filename = NormalizePath(runtime.OutPath + filename);

            NoiseTest3D(filename, noiseValue.Get());

            return Value::Null();
        }
        static Value builtin_noiseTest2D(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "noiseTest2D");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "noiseTest2D");
            std::string filename = GetStringArg(args, 1, "noiseTest2D");

            filename = NormalizePath(runtime.OutPath + filename);

            NoiseTest2D(filename, noiseValue.Get());

            return Value::Null();
        }
        static Value builtin_noiseTest1D(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "noiseTest1D");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "noiseTest1D");
            std::string filename = GetStringArg(args, 1, "noiseTest1D");

            filename = NormalizePath(runtime.OutPath + filename);

            NoiseTest1D(filename, noiseValue.Get());

            return Value::Null();
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

        static Value builtin_displace(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCountAtLeast(args, 3, "displace");
            ExpectArgsCountAtMost(args, 4, "displace");

            Mesh m = GetMeshArg(args, 0, "displace");
            NoiseValue noiseValue = GetNoiseArg(args, 1, "displace");
            float a = GetFloatArg(args, 2, "displace");

            DisplacementTypeEnum displacementType = DisplacementTypeEnum::Normal;
            if(args.size() == 4)
            {
                displacementType = toDisplacementType(args[3].GetIntValue());
            }

            m.Displace(noiseDisplaceFun(noiseValue.Get()), a, displacementType);
            return Value(m);
        }

        void Load(PDSL_Runtime &runtime)
        {
            PLTypeInfo *noiseTypeInfo = runtime.GetNoiseTypeInfo();
            PLTypeInfo *fbmParametersTypeInfo = runtime.FieldsMod->GetFBMParametersTypeInfo();

            runtime.DefineIntrinsicFunction("whiteNoise", builtin_whiteNoise);
            runtime.DefineIntrinsicFunction("valueNoise", builtin_valueNoise);
            runtime.DefineIntrinsicFunction("perlinNoise", builtin_perlinNoise);

            runtime.DefineIntrinsicFunction("ridge", builtin_ridge);
            runtime.DefineFunction("fbm", {noiseTypeInfo, fbmParametersTypeInfo}, builtin_fbm);

            runtime.DefineIntrinsicFunction("abs", builtin_abs);
            runtime.DefineIntrinsicFunction("pow", builtin_pow);

            runtime.DefineIntrinsicFunction("setWhiteNoiseScale", builtin_setWhiteNoiseScale);

            runtime.DefineIntrinsicFunction("subdivide", builtin_subdivide);
            runtime.DefineIntrinsicFunction("tessellate", builtin_tessellate);
            runtime.DefineIntrinsicFunction("projectToUnitSphere", builtin_projectToUnitSphere);
            runtime.DefineIntrinsicFunction("calculateNormals", builtin_calculateNormals);
            runtime.DefineIntrinsicFunction("displace", builtin_displace);

            runtime.DefineIntrinsicFunction("noiseTest", builtin_noiseTest);
            runtime.DefineIntrinsicFunction("noiseTest2D", builtin_noiseTest2D);
            runtime.DefineIntrinsicFunction("noiseTest1D", builtin_noiseTest1D);
        }
    }
}
