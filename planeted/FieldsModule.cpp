#include "FieldsModule.h"
#include "Math.h"
#include "PDSL.h"
#include "PDSL_Utils.h"
#include "PerlinNoise.h"
#include "PGM.h"
#include "PixelMap.h"

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

    static Value builtin_field1(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        float constant = GetFloatArg(args, 0, "pow");

        FieldValue fieldValue(std::make_unique<ConstantField1>(constant));

        return Value(fieldValue);
    }

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

    static Value builtin_fbmField1(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FBMParameters parametersValue = GetFBMParametersArg(args, 1, "fbm");

        FieldValue fieldValue = GetFieldArg(args, 0, "fbm");
        IField1 &field1 = dynamic_cast<IField1&>(fieldValue.Get());

        FieldValue fbmFieldValue(FBMFieldModifier1(field1.Clone1(), parametersValue).Clone());
        return Value(fieldValue);
    }
    static Value builtin_absField1(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "abs");
        IField1 &field1 = dynamic_cast<IField1&>(fieldValue.Get());

        FieldValue absFieldValue(AbsFieldModifier1(field1.Clone1()).Clone());
        return Value(absFieldValue);
    }

    static Value builtin_savePGM(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "savePGM");
        std::string filename = GetStringArg(args, 1, "savePGM");

        filename = NormalizePath(runtime.OutPath + filename);

        uint16_t sample_size = 256;

        IField1 &field1 = dynamic_cast<IField1&>(fieldValue.Get());
        ColorFunction colorFunction = [&field1, sample_size](const int x, const int y)
        {
            float nx = x/static_cast<float>(sample_size) - 0.5f;
            return ToUint8(field1.Eval(nx));
        };

        PixelMap pixelMap = PixelMap(sample_size, sample_size);

        pixelMap.FillRect(0, 0, sample_size, sample_size, colorFunction);

        std::ofstream pgmfile(filename + ".pgm");

        pgmfile << PGM::PixelMapToPGM(pixelMap);

        return Value::Null();
    }

	FieldsModule::FieldsModule(PDSL_Runtime &runtime)
    {
        this->fbmParametersTypeInfo = runtime.DefineType("FBMParamters", ValueTypeEnum::FBMParameters, nullptr);

        this->fieldTypeInfo = runtime.DefineType("Field", ValueTypeEnum::Field, nullptr);
        this->field1TypeInfo = runtime.DefineType("Field1", ValueTypeEnum::Field, this->fieldTypeInfo);

        PLTypeInfo *integerTypeInfo = runtime.GetIntegerTypeInfo();
        PLTypeInfo *stringTypeInfo = runtime.GetStringTypeInfo();
        PLTypeInfo *floatTypeInfo = runtime.GetFloatTypeInfo();
        PLTypeInfo *boolTypeInfo = runtime.GetBooleanTypeInfo();

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

        runtime.DefineFunction("fbm", {this->field1TypeInfo, this->fbmParametersTypeInfo}, builtin_fbmField1);
        runtime.DefineFunction("abs", {this->field1TypeInfo}, builtin_absField1);

        runtime.DefineFunction("savePGM", {this->field1TypeInfo, stringTypeInfo}, builtin_savePGM);
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
