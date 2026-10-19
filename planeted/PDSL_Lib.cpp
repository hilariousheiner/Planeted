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

        static Random::NoiseFunction3D getCurrentNoise(const NoiseFunction &noise)
        {
            return Random::GetNoiseFunction3D(noise.noiseType, noise.noiseStyle);
        }
        static Random::NoiseFunction2D getCurrentNoise2D(const NoiseFunction &noise)
        {
            return Random::GetNoiseFunction2D(noise.noiseType, noise.noiseStyle);
        }
        static Random::NoiseFunction1D getCurrentNoise1D(const NoiseFunction &noise)
        {
            return Random::GetNoiseFunction1D(noise.noiseType, noise.noiseStyle);
        }

        static Value builtin_whiteNoise(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCountAtMost(args, 1, "whiteNoise");

            NoiseValue noiseValue(std::make_unique<NoiseFunction>());
            noiseValue.Get().noiseType = Random::NoiseTypeEnum::White;
            noiseValue.Get().noiseStyle = Random::NoiseStyleEnum::Plain;

            //NoiseValue noiseValue(std::make_unique<WhiteNoise>());

            if(args.size() == 1)
            {
                SeedNoise(noiseValue.Get(), args[0]);
            }
            return Value(noiseValue);
        }
        static Value builtin_valueNoise(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCountAtMost(args, 1, "valueNoise");

            NoiseValue noiseValue(std::make_unique<NoiseFunction>());
            noiseValue.Get().noiseType = Random::NoiseTypeEnum::Value;
            noiseValue.Get().noiseStyle = Random::NoiseStyleEnum::Plain;

            //NoiseValue noiseValue(std::make_unique<ValueNoise>());

            if(args.size() == 1)
            {
                SeedNoise(noiseValue.Get(), args[0]);
            }
            return Value(noiseValue);
        }
        static Value builtin_perlinNoise(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCountAtMost(args, 1, "perlinNoise");

            NoiseValue noiseValue(std::make_unique<NoiseFunction>());
            noiseValue.Get().noiseType = Random::NoiseTypeEnum::Perlin;
            noiseValue.Get().noiseStyle = Random::NoiseStyleEnum::Plain;

            //NoiseValue noiseValue(std::make_unique<PerlinNoise>());

            if(args.size() == 1)
            {
                SeedNoise(noiseValue.Get(), args[0]);
            }
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

            noiseValue.Get().noiseStyle = Random::NoiseStyleEnum::Ridge;
            return Value(noiseValue);

            //NoiseValue ridgedNoiseValue(RidgeNoiseModifier(noiseValue.Get().Clone()).Clone());
            //return Value(ridgedNoiseValue);
        }
        static Value builtin_billow(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "billow");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "billow");

            noiseValue.Get().noiseStyle = Random::NoiseStyleEnum::Billow;
            return Value(noiseValue);

            //NoiseValue billowNoiseValue(BillowNoiseModifier(noiseValue.Get().Clone()).Clone());
            //return Value(billowNoiseValue);
        }

        static Value builtin_setNumberOfOctaves(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setNumberOfOctaves");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "setNumberOfOctaves");
            noiseValue.Get().SetNumberOfOctaves(GetIntArg(args, 1, "setNumberOfOctaves"));

            return Value(noiseValue);
        }
        static Value builtin_setStartFrequency(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setStartFrequency");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "setStartFrequency");
            noiseValue.Get().SetStartFrequency(GetFloatArg(args, 1, "setStartFrequency"));

            return Value(noiseValue);
        }

        static Value builtin_setLacunarity(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setLacunarity");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "setLacunarity");
            noiseValue.Get().SetLacunarity(GetFloatArg(args, 1, "setLacunarity"));

            return Value(noiseValue);
        }

        static Value builtin_setPersistence(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setPersistence");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "setPersistence");
            noiseValue.Get().SetPersistence(GetFloatArg(args, 1, "setPersistence"));

            return Value(noiseValue);
        }

        static Value builtin_setNormalizeFBM(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setNormalizeFBM");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "setNormalizeFBM");
            noiseValue.Get().SetNormalizeFBM(GetBoolArg(args, 1, "setNormalizeFBM"));

            return Value(noiseValue);
        }

        static Value builtin_setWhiteNoiseScale(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setWhiteNoiseScale");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "setWhiteNoiseScale");

            noiseValue.Get().SetWhiteNoiseScale(GetFloatArg(args, 1, "setWhiteNoiseScale"));
            return Value(noiseValue);

            //WhiteNoise &wNoise = dynamic_cast<WhiteNoise&>(noiseValue.Get());
            //wNoise.SetWhiteNoiseScale(GetFloatArg(args, 1, "setWhiteNoiseScale"));
            //return Value(NoiseValue(wNoise.Clone()));
        }

        static Value builtin_noiseTest(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "noiseTest");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "noiseTest");
            std::string filename = GetStringArg(args, 1, "noiseTest");

            filename = NormalizePath(runtime.OutPath + filename);

            NoiseTest3D(filename, noiseValue.Get().fbmParams, noiseValue.Get().noiseParams, PDSL_Lib::getCurrentNoise(noiseValue.Get()));
            //NoiseTest3D(filename, noiseValue.Get());

            return Value::Null();
        }
        static Value builtin_noiseTest2D(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "noiseTest2D");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "noiseTest2D");
            std::string filename = GetStringArg(args, 1, "noiseTest2D");

            filename = NormalizePath(runtime.OutPath + filename);

            NoiseTest2D(filename, noiseValue.Get().fbmParams, noiseValue.Get().noiseParams, PDSL_Lib::getCurrentNoise2D(noiseValue.Get()));
            //NoiseTest2D(filename, noiseValue.Get());

            return Value::Null();
        }
        static Value builtin_noiseTest1D(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "noiseTest1D");

            NoiseValue noiseValue = GetNoiseArg(args, 0, "noiseTest1D");
            std::string filename = GetStringArg(args, 1, "noiseTest1D");

            filename = NormalizePath(runtime.OutPath + filename);

            NoiseTest1D(filename, noiseValue.Get().fbmParams, noiseValue.Get().noiseParams, PDSL_Lib::getCurrentNoise1D(noiseValue.Get()));
            //NoiseTest1D(filename, noiseValue.Get());

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

        static DisplacementFunction noiseDisplaceFun(const NoiseFunction &noise)
        {
            return [noise](const Vector3 &v)
            {
                return Random::FBM3D(v, noise.fbmParams, noise.noiseParams, PDSL_Lib::getCurrentNoise(noise));
            };
        }

        static DisplacementFunction noiseDisplaceFun(const ANoise &noise)
        {
            return [&noise](const Vector3 &v)
            {
                return noise.Eval3D(v);
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

            runtime.InstallBuiltinFunction("seedNoise", builtin_seedNoise);

            runtime.InstallBuiltinFunction("ridge", builtin_ridge);
            runtime.InstallBuiltinFunction("billow", builtin_billow);

            runtime.InstallBuiltinFunction("setWhiteNoiseScale", builtin_setWhiteNoiseScale);

            runtime.InstallBuiltinFunction("setNumberOfOctaves", builtin_setNumberOfOctaves);
            runtime.InstallBuiltinFunction("setStartFrequency", builtin_setStartFrequency);
            runtime.InstallBuiltinFunction("setLacunarity", builtin_setLacunarity);
            runtime.InstallBuiltinFunction("setPersistence", builtin_setPersistence);
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
