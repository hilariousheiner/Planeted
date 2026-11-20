#include "FieldsModule.h"
#include "Math.h"
#include "PDSL.h"
#include "PDSL_Utils.h"
#include "PerlinNoise.h"
#include "PGM.h"
#include "PixelMap.h"
#include "ValueNoise.h"
#include "WhiteNoise.h"

namespace Planeted
{
    static Value builtin_setSeedFromInteger(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "setSeed"); // note: this performs checks that are now redundant; replace by something else.
        int seed = GetIntArg(args, 1, "setSeed"); // note: this performs checks that are now redundant; replace by something else.

        fieldValue.Get().SetSeed(seed);

        return Value(fieldValue);
    }
    static Value builtin_setSeedFromString(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "setSeed"); // note: this performs checks that are now redundant; replace by something else.
        std::string seed = GetStringArg(args, 1, "setSeed"); // note: this performs checks that are now redundant; replace by something else.

        fieldValue.Get().SetSeed(seed);

        return Value(fieldValue);
    }

    static Value builtin_perlinNoise1(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<PerlinNoise1>());

        return Value(fieldValue);
    }
    static Value builtin_perlinNoise1FromString(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<PerlinNoise1>());

        std::string seed = GetStringArg(args, 0, "perlinNoise1"); // note: this performs checks that are now redundant; replace by something else.

        fieldValue.Get().SetSeed(seed);

        return Value(fieldValue);
    }
    static Value builtin_perlinNoise1FromInteger(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<PerlinNoise1>());

        int seed = GetIntArg(args, 0, "perlinNoise1"); // note: this performs checks that are now redundant; replace by something else.

        fieldValue.Get().SetSeed(seed);

        return Value(fieldValue);
    }

    //------------------------------------------

    static Value builtin_perlinNoise2(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<PerlinNoise2>());

        return Value(fieldValue);
    }
    static Value builtin_perlinNoise2FromString(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<PerlinNoise2>());

        std::string seed = GetStringArg(args, 0, "perlinNoise2"); // note: this performs checks that are now redundant; replace by something else.

        fieldValue.Get().SetSeed(seed);

        return Value(fieldValue);
    }
    static Value builtin_perlinNoise2FromInteger(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<PerlinNoise1>());

        int seed = GetIntArg(args, 0, "perlinNoise2"); // note: this performs checks that are now redundant; replace by something else.

        fieldValue.Get().SetSeed(seed);

        return Value(fieldValue);
    }

    //------------------------------------------

    static Value builtin_whiteNoise1(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<WhiteNoise1>());

        return Value(fieldValue);
    }
    static Value builtin_whiteNoise1FromString(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<WhiteNoise1>());

        std::string seed = GetStringArg(args, 0, "whiteNoise1"); // note: this performs checks that are now redundant; replace by something else.

        fieldValue.Get().SetSeed(seed);

        return Value(fieldValue);
    }
    static Value builtin_whiteNoise1FromInteger(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<WhiteNoise1>());

        int seed = GetIntArg(args, 0, "whiteNoise1"); // note: this performs checks that are now redundant; replace by something else.

        fieldValue.Get().SetSeed(seed);

        return Value(fieldValue);
    }

    static Value builtin_setWhiteNoise1Scale(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "setWhiteNoiseScale");

        WhiteNoise1 &wNoise1 = dynamic_cast<WhiteNoise1&>(fieldValue.Get());
        wNoise1.SetWhiteNoiseScale(GetFloatArg(args, 1, "setWhiteNoiseScale"));

        return Value(FieldValue(wNoise1.Clone()));
    }

    //-----------------------------------------

    static Value builtin_whiteNoise2(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<WhiteNoise2>());

        return Value(fieldValue);
    }
    static Value builtin_whiteNoise2FromString(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<WhiteNoise2>());

        std::string seed = GetStringArg(args, 0, "whiteNoise2"); // note: this performs checks that are now redundant; replace by something else.

        fieldValue.Get().SetSeed(seed);

        return Value(fieldValue);
    }
    static Value builtin_whiteNoise2FromInteger(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<WhiteNoise2>());

        int seed = GetIntArg(args, 0, "whiteNoise2"); // note: this performs checks that are now redundant; replace by something else.

        fieldValue.Get().SetSeed(seed);

        return Value(fieldValue);
    }

    static Value builtin_setWhiteNoise2Scale(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "setWhiteNoiseScale");

        WhiteNoise2 &wNoise2 = dynamic_cast<WhiteNoise2&>(fieldValue.Get());
        wNoise2.SetWhiteNoiseScale(GetFloatArg(args, 1, "setWhiteNoiseScale"));

        return Value(FieldValue(wNoise2.Clone()));
    }

    //-----------------------------------------

    static Value builtin_whiteNoise3(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<WhiteNoise3>());

        return Value(fieldValue);
    }
    static Value builtin_whiteNoise3FromString(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<WhiteNoise3>());

        std::string seed = GetStringArg(args, 0, "whiteNoise3"); // note: this performs checks that are now redundant; replace by something else.

        fieldValue.Get().SetSeed(seed);

        return Value(fieldValue);
    }
    static Value builtin_whiteNoise3FromInteger(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<WhiteNoise3>());

        int seed = GetIntArg(args, 0, "whiteNoise3"); // note: this performs checks that are now redundant; replace by something else.

        fieldValue.Get().SetSeed(seed);

        return Value(fieldValue);
    }

    static Value builtin_setWhiteNoise3Scale(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "setWhiteNoiseScale");

        WhiteNoise3 &wNoise3 = dynamic_cast<WhiteNoise3&>(fieldValue.Get());
        wNoise3.SetWhiteNoiseScale(GetFloatArg(args, 1, "setWhiteNoiseScale"));

        return Value(FieldValue(wNoise3.Clone()));
    }

    //-----------------------------------------

    static Value builtin_valueNoise1(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<ValueNoise1>());

        return Value(fieldValue);
    }
    static Value builtin_valueNoise1FromString(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<ValueNoise1>());

        std::string seed = GetStringArg(args, 0, "valueNoise1"); // note: this performs checks that are now redundant; replace by something else.

        fieldValue.Get().SetSeed(seed);

        return Value(fieldValue);
    }
    static Value builtin_valueNoise1FromInteger(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<ValueNoise1>());

        int seed = GetIntArg(args, 0, "valueNoise1"); // note: this performs checks that are now redundant; replace by something else.

        fieldValue.Get().SetSeed(seed);

        return Value(fieldValue);
    }

    static Value builtin_valueNoise2(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<ValueNoise2>());

        return Value(fieldValue);
    }
    static Value builtin_valueNoise2FromString(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<ValueNoise2>());

        std::string seed = GetStringArg(args, 0, "valueNoise2"); // note: this performs checks that are now redundant; replace by something else.

        fieldValue.Get().SetSeed(seed);

        return Value(fieldValue);
    }
    static Value builtin_valueNoise2FromInteger(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<ValueNoise2>());

        int seed = GetIntArg(args, 0, "valueNoise2"); // note: this performs checks that are now redundant; replace by something else.

        fieldValue.Get().SetSeed(seed);

        return Value(fieldValue);
    }

    static Value builtin_valueNoise3(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<ValueNoise3>());

        return Value(fieldValue);
    }
    static Value builtin_valueNoise3FromString(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<ValueNoise3>());

        std::string seed = GetStringArg(args, 0, "valueNoise3"); // note: this performs checks that are now redundant; replace by something else.

        fieldValue.Get().SetSeed(seed);

        return Value(fieldValue);
    }
    static Value builtin_valueNoise3FromInteger(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue(std::make_unique<ValueNoise3>());

        int seed = GetIntArg(args, 0, "valueNoise3"); // note: this performs checks that are now redundant; replace by something else.

        fieldValue.Get().SetSeed(seed);

        return Value(fieldValue);
    }

    //--------------------------------------------
    static Value builtin_field1(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        float constant = GetFloatArg(args, 0, "pow");

        FieldValue fieldValue(std::make_unique<ConstantField1>(constant));

        return Value(fieldValue);
    }

    //------------------------------------------------

    static Value builtin_fbmParameters(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FBMParameters parametersValue;

        return Value(parametersValue);
    }
    static Value builtin_setNumberOfOctaves(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FBMParameters parametersValue = GetFBMParametersArg(args, 0, "setNumberOfOctaves");
        parametersValue.NumberOfOctaves = GetIntArg(args, 1, "setNumberOfOctaves");

        return Value(parametersValue);
    }
    static Value builtin_setLacunarity(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FBMParameters parametersValue = GetFBMParametersArg(args, 0, "setLacunarity");
        parametersValue.Lacunarity = GetFloatArg(args, 1, "setLacunarity");

        return Value(parametersValue);
    }
    static Value builtin_setPersistence(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FBMParameters parametersValue = GetFBMParametersArg(args, 0, "setPersistence");
        parametersValue.Persistence = GetFloatArg(args, 1, "setPersistence");

        return Value(parametersValue);
    }
    static Value builtin_setStartFrequency(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FBMParameters parametersValue = GetFBMParametersArg(args, 0, "setStartFrequency");
        parametersValue.StartFrequency = GetFloatArg(args, 1, "setStartFrequency");

        return Value(parametersValue);
    }
    static Value builtin_setNormalizeFBM(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FBMParameters parametersValue = GetFBMParametersArg(args, 0, "setNormalizeFBM");
        parametersValue.Normalize = GetBoolArg(args, 1, "setNormalizeFBM");

        return Value(parametersValue);
    }

    //--------------------------------------------------

    static Value builtin_fbmField1(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "fbm");
        AField1 &field1 = dynamic_cast<AField1&>(fieldValue.Get());

        FBMParameters parametersValue = GetFBMParametersArg(args, 1, "fbm");

        FieldValue fbmFieldValue(FBMFieldModifier1(field1.Clone1(), parametersValue).Clone());
        return Value(fbmFieldValue);
    }
    static Value builtin_fbmField2(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "fbm");
        AField2 &field2 = dynamic_cast<AField2&>(fieldValue.Get());

        FBMParameters parametersValue = GetFBMParametersArg(args, 1, "fbm");

        FieldValue fbmFieldValue(FBMFieldModifier2(field2.Clone2(), parametersValue).Clone());
        return Value(fbmFieldValue);
    }
    static Value builtin_fbmField3(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "fbm");
        AField3 &field3 = dynamic_cast<AField3&>(fieldValue.Get());

        FBMParameters parametersValue = GetFBMParametersArg(args, 1, "fbm");

        FieldValue fbmFieldValue(FBMFieldModifier3(field3.Clone3(), parametersValue).Clone());
        return Value(fbmFieldValue);
    }

    static Value builtin_ridgeField1(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "ridge");
        AField1 &field1 = dynamic_cast<AField1&>(fieldValue.Get());

        FieldValue ridgeFieldValue(RidgeFieldModifier1(field1.Clone1()).Clone());
        return Value(ridgeFieldValue);
    }
    static Value builtin_ridgeField2(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "ridge");
        AField2 &field2 = dynamic_cast<AField2&>(fieldValue.Get());

        FieldValue ridgeFieldValue(RidgeFieldModifier2(field2.Clone2()).Clone());
        return Value(ridgeFieldValue);
    }
    static Value builtin_ridgeField3(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "ridge");
        AField3 &field3 = dynamic_cast<AField3&>(fieldValue.Get());

        FieldValue ridgeFieldValue(RidgeFieldModifier3(field3.Clone3()).Clone());
        return Value(ridgeFieldValue);
    }

    static Value builtin_absField1(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "abs");
        AField1 &field1 = dynamic_cast<AField1&>(fieldValue.Get());

        FieldValue absFieldValue(AbsFieldModifier1(field1.Clone1()).Clone());
        return Value(absFieldValue);
    }
    static Value builtin_absField2(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "abs");
        AField2 &field2 = dynamic_cast<AField2&>(fieldValue.Get());

        FieldValue absFieldValue(AbsFieldModifier2(field2.Clone2()).Clone());
        return Value(absFieldValue);
    }
    static Value builtin_absField3(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "abs");
        AField3 &field3 = dynamic_cast<AField3&>(fieldValue.Get());

        FieldValue absFieldValue(AbsFieldModifier3(field3.Clone3()).Clone());
        return Value(absFieldValue);
    }

    static Value builtin_powField1(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "pow");
        AField1 &field1 = dynamic_cast<AField1&>(fieldValue.Get());

        float exponent = GetFloatArg(args, 1, "pow");

        FieldValue powFieldValue(PowFieldModifier1(field1.Clone1(), exponent).Clone());
        return Value(powFieldValue);
    }
    static Value builtin_powField2(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "pow");
        AField2 &field2 = dynamic_cast<AField2&>(fieldValue.Get());

        float exponent = GetFloatArg(args, 1, "pow");

        FieldValue powFieldValue(PowFieldModifier2(field2.Clone2(), exponent).Clone());
        return Value(powFieldValue);
    }
    static Value builtin_powField3(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "pow");
        AField3 &field3 = dynamic_cast<AField3&>(fieldValue.Get());

        float exponent = GetFloatArg(args, 1, "pow");

        FieldValue powFieldValue(PowFieldModifier3(field3.Clone3(), exponent).Clone());
        return Value(powFieldValue);
    }

    //------------------------------------------------------

    static Value builtin_savePGM1(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "savePGM");
        std::string filename = GetStringArg(args, 1, "savePGM");

        filename = NormalizePath(runtime.OutPath + filename);

        uint16_t sample_size = 256;

        AField1 &field1 = dynamic_cast<AField1&>(fieldValue.Get());
        ColorFunction colorFunction = [&field1, sample_size](const int x, const int y)
        {
            float nx = x/static_cast<float>(sample_size) - 0.5f;
            return ToUint8(SignedToUnitRange(field1.Eval(nx)));
        };

        PixelMap pixelMap = PixelMap(sample_size, sample_size);

        pixelMap.FillRect(0, 0, sample_size, sample_size, colorFunction);

        std::ofstream pgmfile(filename + ".pgm");

        pgmfile << PGM::PixelMapToPGM(pixelMap);

        return Value::Null();
    }
    static Value builtin_savePGM2(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "savePGM");
        std::string filename = GetStringArg(args, 1, "savePGM");

        filename = NormalizePath(runtime.OutPath + filename);

        uint16_t sample_size = 256;

        AField2 &field2 = dynamic_cast<AField2&>(fieldValue.Get());
        ColorFunction colorFunction = [&field2, sample_size](const int x, const int y)
        {
            float nx = x/static_cast<float>(sample_size) - 0.5f;
            float ny = y/static_cast<float>(sample_size) - 0.5f;
            return ToUint8(SignedToUnitRange(field2.Eval({nx, ny})));
        };

        PixelMap pixelMap = PixelMap(sample_size, sample_size);

        pixelMap.FillRect(0, 0, sample_size, sample_size, colorFunction);

        std::ofstream pgmfile(filename + ".pgm");

        pgmfile << PGM::PixelMapToPGM(pixelMap);

        return Value::Null();
    }
    static Value builtin_savePGM3(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "savePGM");
        std::string filename = GetStringArg(args, 1, "savePGM");

        filename = NormalizePath(runtime.OutPath + filename);

        uint16_t sample_size = 256;

        AField3 &field3 = dynamic_cast<AField3&>(fieldValue.Get());
        ColorFunction colorFunction = [&field3, sample_size](const int x, const int y)
        {
            float nx = x/static_cast<float>(sample_size) - 0.5f;
            float ny = y/static_cast<float>(sample_size) - 0.5f;
            return ToUint8(SignedToUnitRange(field3.Eval({nx, ny, 1.0f})));
        };

        PixelMap pixelMap = PixelMap(sample_size, sample_size);

        pixelMap.FillRect(0, 0, sample_size, sample_size, colorFunction);

        std::ofstream pgmfile(filename + ".pgm");

        pgmfile << PGM::PixelMapToPGM(pixelMap);

        return Value::Null();
    }

    //ToDo: move to mesh module as soon as that's available
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

	FieldsModule::FieldsModule(PDSL_Runtime &runtime)
    {
        this->fbmParametersTypeInfo = runtime.DefineType("FBMParamters", ValueTypeEnum::FBMParameters, nullptr);

        this->fieldTypeInfo = runtime.DefineType("Field", ValueTypeEnum::Field, nullptr);
        this->field1TypeInfo = runtime.DefineType("Field1", ValueTypeEnum::Field, this->fieldTypeInfo);
        this->field2TypeInfo = runtime.DefineType("Field2", ValueTypeEnum::Field, this->fieldTypeInfo);
        this->field3TypeInfo = runtime.DefineType("Field3", ValueTypeEnum::Field, this->fieldTypeInfo);

        this->whiteNoise1TypeInfo = runtime.DefineType("WhiteNoise1", ValueTypeEnum::Field, this->field1TypeInfo);
        this->whiteNoise2TypeInfo = runtime.DefineType("WhiteNoise2", ValueTypeEnum::Field, this->field2TypeInfo);
        this->whiteNoise3TypeInfo = runtime.DefineType("WhiteNoise3", ValueTypeEnum::Field, this->field3TypeInfo);

        PLTypeInfo *integerTypeInfo = runtime.GetIntegerTypeInfo();
        PLTypeInfo *stringTypeInfo = runtime.GetStringTypeInfo();
        PLTypeInfo *floatTypeInfo = runtime.GetFloatTypeInfo();
        PLTypeInfo *boolTypeInfo = runtime.GetBooleanTypeInfo();
        PLTypeInfo *meshTypeInfo = runtime.GetMeshTypeInfo();

        runtime.DefineFunction("setSeed", {this->fieldTypeInfo, integerTypeInfo}, builtin_setSeedFromInteger);
        runtime.DefineFunction("setSeed", {this->fieldTypeInfo, stringTypeInfo}, builtin_setSeedFromString);

        runtime.DefineFunction("fbmParameters", {}, builtin_fbmParameters);
        runtime.DefineFunction("setNumberOfOctaves", {this->fbmParametersTypeInfo, integerTypeInfo}, builtin_setNumberOfOctaves);
        runtime.DefineFunction("setLacunarity",{this->fbmParametersTypeInfo, floatTypeInfo}, builtin_setLacunarity);
        runtime.DefineFunction("setPersistence", {this->fbmParametersTypeInfo, floatTypeInfo}, builtin_setPersistence);
        runtime.DefineFunction("setStartFrequency", {this->fbmParametersTypeInfo, floatTypeInfo}, builtin_setStartFrequency);
        runtime.DefineFunction("setNormalizeFBM", {this->fbmParametersTypeInfo, boolTypeInfo}, builtin_setNormalizeFBM);

        runtime.DefineFunction("field1", {this->fbmParametersTypeInfo, floatTypeInfo}, builtin_field1);

        runtime.DefineFunction("perlinNoise1", {}, builtin_perlinNoise1);
        runtime.DefineFunction("perlinNoise1", {integerTypeInfo}, builtin_perlinNoise1FromInteger);
        runtime.DefineFunction("perlinNoise1", {stringTypeInfo}, builtin_perlinNoise1FromString);

        runtime.DefineFunction("perlinNoise2", {}, builtin_perlinNoise2);
        runtime.DefineFunction("perlinNoise2", {integerTypeInfo}, builtin_perlinNoise2FromInteger);
        runtime.DefineFunction("perlinNoise2", {stringTypeInfo}, builtin_perlinNoise2FromString);

        runtime.DefineFunction("valueNoise1", {}, builtin_valueNoise1);
        runtime.DefineFunction("valueNoise1", {integerTypeInfo}, builtin_valueNoise1FromInteger);
        runtime.DefineFunction("valueNoise1", {stringTypeInfo}, builtin_valueNoise1FromString);

        runtime.DefineFunction("valueNoise2", {}, builtin_valueNoise2);
        runtime.DefineFunction("valueNoise2", {integerTypeInfo}, builtin_valueNoise2FromInteger);
        runtime.DefineFunction("valueNoise2", {stringTypeInfo}, builtin_valueNoise2FromString);

        runtime.DefineFunction("valueNoise3", {}, builtin_valueNoise3);
        runtime.DefineFunction("valueNoise3", {integerTypeInfo}, builtin_valueNoise3FromInteger);
        runtime.DefineFunction("valueNoise3", {stringTypeInfo}, builtin_valueNoise3FromString);

        runtime.DefineFunction("whiteNoise1", {}, builtin_whiteNoise1);
        runtime.DefineFunction("whiteNoise1", {integerTypeInfo}, builtin_whiteNoise1FromInteger);
        runtime.DefineFunction("whiteNoise1", {stringTypeInfo}, builtin_whiteNoise1FromString);

        runtime.DefineFunction("whiteNoise2", {}, builtin_whiteNoise2);
        runtime.DefineFunction("whiteNoise2", {integerTypeInfo}, builtin_whiteNoise2FromInteger);
        runtime.DefineFunction("whiteNoise2", {stringTypeInfo}, builtin_whiteNoise2FromString);

        runtime.DefineFunction("whiteNoise3", {}, builtin_whiteNoise3);
        runtime.DefineFunction("whiteNoise3", {integerTypeInfo}, builtin_whiteNoise3FromInteger);
        runtime.DefineFunction("whiteNoise3", {stringTypeInfo}, builtin_whiteNoise3FromString);

        runtime.DefineFunction("setWhiteNoiseScale", {this->whiteNoise1TypeInfo, floatTypeInfo}, builtin_setWhiteNoise1Scale);
        runtime.DefineFunction("setWhiteNoiseScale", {this->whiteNoise2TypeInfo, floatTypeInfo}, builtin_setWhiteNoise2Scale);
        runtime.DefineFunction("setWhiteNoiseScale", {this->whiteNoise3TypeInfo, floatTypeInfo}, builtin_setWhiteNoise3Scale);

        runtime.DefineFunction("fbm", {this->field1TypeInfo, this->fbmParametersTypeInfo}, builtin_fbmField1);
        runtime.DefineFunction("fbm", {this->field2TypeInfo, this->fbmParametersTypeInfo}, builtin_fbmField2);
        runtime.DefineFunction("fbm", {this->field3TypeInfo, this->fbmParametersTypeInfo}, builtin_fbmField3);

        runtime.DefineFunction("ridge", {this->field1TypeInfo}, builtin_ridgeField1);
        runtime.DefineFunction("ridge", {this->field2TypeInfo}, builtin_ridgeField2);
        runtime.DefineFunction("ridge", {this->field3TypeInfo}, builtin_ridgeField3);

        runtime.DefineFunction("abs", {this->field1TypeInfo}, builtin_absField1);
        runtime.DefineFunction("abs", {this->field2TypeInfo}, builtin_absField2);
        runtime.DefineFunction("abs", {this->field3TypeInfo}, builtin_absField3);

        runtime.DefineFunction("pow", {this->field1TypeInfo, floatTypeInfo}, builtin_powField1);
        runtime.DefineFunction("pow", {this->field2TypeInfo, floatTypeInfo}, builtin_powField2);
        runtime.DefineFunction("pow", {this->field3TypeInfo, floatTypeInfo}, builtin_powField3);

        runtime.DefineFunction("savePGM", {this->field1TypeInfo, stringTypeInfo}, builtin_savePGM1);
        runtime.DefineFunction("savePGM", {this->field2TypeInfo, stringTypeInfo}, builtin_savePGM2);
        runtime.DefineFunction("savePGM", {this->field3TypeInfo, stringTypeInfo}, builtin_savePGM3);

        runtime.DefineFunction("displace", {meshTypeInfo, this->field3TypeInfo, floatTypeInfo}, builtin_displaceNormal);

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
    PLTypeInfo *FieldsModule::GetField2TypeInfo() const
    {
        return this->field2TypeInfo;
    }
    PLTypeInfo *FieldsModule::GetField3TypeInfo() const
    {
        return this->field3TypeInfo;
    }

    PLTypeInfo *FieldsModule::GetWhiteNoise1TypeInfo() const
    {
        return this->whiteNoise1TypeInfo;
    }
    PLTypeInfo *FieldsModule::GetWhiteNoise2TypeInfo() const
    {
        return this->whiteNoise2TypeInfo;
    }
    PLTypeInfo *FieldsModule::GetWhiteNoise3TypeInfo() const
    {
        return this->whiteNoise3TypeInfo;
    }
}
