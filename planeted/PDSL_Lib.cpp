#include "PDSL_Lib.h"

#include <memory>
#include <iostream>

#include "Noise.h"
#include "PDSL_Utils.h"
#include "Random.h"
#include "Tests.h"

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
                SeedNoise(noiseValue.Get(), args[0]);
            }
            return Value(noiseValue);
        }
        static Value builtin_valueNoise(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCountAtMost(args, 1, "valueNoise");

            NoiseValue noiseValue(std::make_unique<ValueNoise>());

            if(args.size() == 1)
            {
                SeedNoise(noiseValue.Get(), args[0]);
            }
            return Value(noiseValue);
        }
        static Value builtin_perlinNoise(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCountAtMost(args, 1, "perlinNoise");
            NoiseValue noiseValue(std::make_unique<PerlinNoise>());

            if(args.size() == 1)
            {
                SeedNoise(noiseValue.Get(), args[0]);
            }
            return Value(noiseValue);
        }

        static Value builtin_fbmParameters(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 0, "fbmParameters");

            FBMParameters parametersValue;

            return Value(parametersValue);
        }

        static Value builtin_fbm(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "fbm");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "fbm");
            FBMParameters parametersValue = GetFBMParametersArg(args, 1, "fbm");

            noiseValue.Get().SetFBMParameters(parametersValue);

            return Value(noiseValue);
        }

        static Value builtin_seedNoise(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "seedNoise");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "seedNoise");

            SeedNoise(noiseValue.Get(), args[1]);

            return Value(noiseValue);
        }

        static Value builtin_ridge(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "ridge");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "ridge");

            NoiseValue ridgedNoiseValue(RidgeNoiseModifier(noiseValue.Get().Clone()).Clone());
            return Value(ridgedNoiseValue);
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


        static Value builtin_setNumberOfOctaves(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setNumberOfOctaves");

            FBMParameters parametersValue = GetFBMParametersArg(args, 0, "setNumberOfOctaves");
            parametersValue.NumberOfOctaves = GetIntArg(args, 1, "setNumberOfOctaves");

            return Value(parametersValue);
        }
        /*
        static Value builtin_setNumberOfOctaves(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setNumberOfOctaves");

            if(args[0].GetValueType() == ValueTypeEnum::Noise)
            {
                NoiseValue noiseValue = GetNoiseArg(args, 0, "setNumberOfOctaves");
                noiseValue.Get().SetNumberOfOctaves(GetIntArg(args, 1, "setNumberOfOctaves"));

                return Value(noiseValue);
            }

            if(args[0].GetValueType() == ValueTypeEnum::FBMParameters)
            {
                FBMParameters parametersValue = GetFBMParametersArg(args, 0, "setNumberOfOctaves");
                parametersValue.NumberOfOctaves = GetIntArg(args, 1, "setNumberOfOctaves");

                return Value(parametersValue);
            }
            throw std::runtime_error("first paramter of setNumberOfOctaves must be a noise or FBMParameters.");
        }
        */
        /*
        static Value builtin_setLacunarity(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setLacunarity");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "setLacunarity");
            noiseValue.Get().SetLacunarity(GetFloatArg(args, 1, "setLacunarity"));

            return Value(noiseValue);
        }
        */
        static Value builtin_setLacunarity(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setLacunarity");

            if(args[0].GetValueType() == ValueTypeEnum::Noise)
            {
                NoiseValue noiseValue = GetNoiseArg(args, 0, "setLacunarity");
                noiseValue.Get().SetLacunarity(GetFloatArg(args, 1, "setLacunarity"));

                return Value(noiseValue);
            }

            if(args[0].GetValueType() == ValueTypeEnum::FBMParameters)
            {
                FBMParameters parametersValue = GetFBMParametersArg(args, 0, "setLacunarity");
                parametersValue.Lacunarity = GetFloatArg(args, 1, "setLacunarity");

                return Value(parametersValue);
            }
            throw std::runtime_error("first paramter of setLacunarity must be a noise or FBMParameters.");
        }
        /*
        static Value builtin_setPersistence(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setPersistence");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "setPersistence");
            noiseValue.Get().SetPersistence(GetFloatArg(args, 1, "setPersistence"));

            return Value(noiseValue);
        }
        */
        static Value builtin_setPersistence(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setPersistence");

            if(args[0].GetValueType() == ValueTypeEnum::Noise)
            {
                NoiseValue noiseValue = GetNoiseArg(args, 0, "setPersistence");
                noiseValue.Get().SetPersistence(GetFloatArg(args, 1, "setPersistence"));

                return Value(noiseValue);
            }

            if(args[0].GetValueType() == ValueTypeEnum::FBMParameters)
            {
                FBMParameters parametersValue = GetFBMParametersArg(args, 0, "setPersistence");
                parametersValue.Persistence = GetFloatArg(args, 1, "setPersistence");

                return Value(parametersValue);
            }
            throw std::runtime_error("first paramter of setPersistence must be a noise or FBMParameters.");
        }
        /*
        static Value builtin_setStartFrequency(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setStartFrequency");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "setStartFrequency");
            noiseValue.Get().SetStartFrequency(GetFloatArg(args, 1, "setStartFrequency"));

            return Value(noiseValue);
        }
        */
        static Value builtin_setStartFrequency(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setStartFrequency");

            if(args[0].GetValueType() == ValueTypeEnum::Noise)
            {
                NoiseValue noiseValue = GetNoiseArg(args, 0, "setStartFrequency");
                noiseValue.Get().SetStartFrequency(GetFloatArg(args, 1, "setStartFrequency"));

                return Value(noiseValue);
            }

            if(args[0].GetValueType() == ValueTypeEnum::FBMParameters)
            {
                FBMParameters parametersValue = GetFBMParametersArg(args, 0, "setStartFrequency");
                parametersValue.StartFrequency = GetFloatArg(args, 1, "setStartFrequency");

                return Value(parametersValue);
            }
            throw std::runtime_error("first paramter of setStartFrequency must be a noise or FBMParameters.");
        }
        /*
        static Value builtin_setNormalizeFBM(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setNormalizeFBM");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "setNormalizeFBM");
            noiseValue.Get().SetNormalizeFBM(GetBoolArg(args, 1, "setNormalizeFBM"));

            return Value(noiseValue);
        }
        */
        static Value builtin_setNormalizeFBM(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setNormalizeFBM");

            if(args[0].GetValueType() == ValueTypeEnum::Noise)
            {
                NoiseValue noiseValue = GetNoiseArg(args, 0, "setNormalizeFBM");
                noiseValue.Get().SetNormalizeFBM(GetBoolArg(args, 1, "setNormalizeFBM"));

                return Value(noiseValue);
            }

            if(args[0].GetValueType() == ValueTypeEnum::FBMParameters)
            {
                FBMParameters parametersValue = GetFBMParametersArg(args, 0, "setNormalizeFBM");
                parametersValue.Normalize = GetBoolArg(args, 1, "setNormalizeFBM");

                return Value(parametersValue);
            }
            throw std::runtime_error("first paramter of setNormalizeFBM must be a noise or FBMParameters.");
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
            runtime.InstallBuiltinFunction("whiteNoise", builtin_whiteNoise);
            runtime.InstallBuiltinFunction("valueNoise", builtin_valueNoise);
            runtime.InstallBuiltinFunction("perlinNoise", builtin_perlinNoise);

            runtime.InstallBuiltinFunction("fbmParameters", builtin_fbmParameters);
            runtime.InstallBuiltinFunction("fbm", builtin_fbm);

            runtime.InstallBuiltinFunction("seedNoise", builtin_seedNoise);

            runtime.InstallBuiltinFunction("ridge", builtin_ridge);

            runtime.InstallBuiltinFunction("abs", builtin_abs);
            runtime.InstallBuiltinFunction("pow", builtin_pow);

            runtime.InstallBuiltinFunction("setWhiteNoiseScale", builtin_setWhiteNoiseScale);

            runtime.InstallBuiltinFunction("setNumberOfOctaves", builtin_setNumberOfOctaves);
            runtime.InstallBuiltinFunction("setLacunarity", builtin_setLacunarity);
            runtime.InstallBuiltinFunction("setPersistence", builtin_setPersistence);
            runtime.InstallBuiltinFunction("setStartFrequency", builtin_setStartFrequency);
            runtime.InstallBuiltinFunction("setNormalizeFBM", builtin_setNormalizeFBM);

            runtime.InstallBuiltinFunction("subdivide", builtin_subdivide);
            runtime.InstallBuiltinFunction("tessellate", builtin_tessellate);
            runtime.InstallBuiltinFunction("projectToUnitSphere", builtin_projectToUnitSphere);
            runtime.InstallBuiltinFunction("calculateNormals", builtin_calculateNormals);
            runtime.InstallBuiltinFunction("displace", builtin_displace);

            runtime.InstallBuiltinFunction("noiseTest", builtin_noiseTest);
            runtime.InstallBuiltinFunction("noiseTest2D", builtin_noiseTest2D);
            runtime.InstallBuiltinFunction("noiseTest1D", builtin_noiseTest1D);
        }
    }
}
