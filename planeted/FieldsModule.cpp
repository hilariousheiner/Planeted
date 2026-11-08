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

    static Value builtin_field1(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        ExpectArgsCount(args, 1, "field1");

        float constant = GetFloatArg(args, 0, "pow");

        FieldValue fieldValue(std::make_unique<ConstantField1>(constant));

        return Value(fieldValue);
    }

    static Value builtin_perlinNoise1(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        ExpectArgsCountAtMost(args, 1, "perlinNoise1");
        FieldValue fieldValue(std::make_unique<PerlinNoise1>());

        if(args.size() == 1)
        {
            SetSeed(fieldValue.Get(), args[0]);
        }
        return Value(fieldValue);
    }

    static Value builtin_fbmParameters(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        ExpectArgsCount(args, 0, "fbmParameters");

        FBMParameters parametersValue;

        return Value(parametersValue);
    }
    static Value builtin_setNumberOfOctaves(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        ExpectArgsCount(args, 2, "setNumberOfOctaves");

        FBMParameters parametersValue = GetFBMParametersArg(args, 0, "setNumberOfOctaves");
        parametersValue.NumberOfOctaves = GetIntArg(args, 1, "setNumberOfOctaves");

        return Value(parametersValue);
    }
    static Value builtin_setLacunarity(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        ExpectArgsCount(args, 2, "setLacunarity");

        FBMParameters parametersValue = GetFBMParametersArg(args, 0, "setLacunarity");
        parametersValue.Lacunarity = GetFloatArg(args, 1, "setLacunarity");

        return Value(parametersValue);
    }
    static Value builtin_setPersistence(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        ExpectArgsCount(args, 2, "setPersistence");

        FBMParameters parametersValue = GetFBMParametersArg(args, 0, "setPersistence");
        parametersValue.Persistence = GetFloatArg(args, 1, "setPersistence");

        return Value(parametersValue);
    }
    static Value builtin_setStartFrequency(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        ExpectArgsCount(args, 2, "setStartFrequency");

        FBMParameters parametersValue = GetFBMParametersArg(args, 0, "setStartFrequency");
        parametersValue.StartFrequency = GetFloatArg(args, 1, "setStartFrequency");

        return Value(parametersValue);
    }
    static Value builtin_setNormalizeFBM(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        ExpectArgsCount(args, 2, "setNormalizeFBM");

        FBMParameters parametersValue = GetFBMParametersArg(args, 0, "setNormalizeFBM");
        parametersValue.Normalize = GetBoolArg(args, 1, "setNormalizeFBM");

        return Value(parametersValue);
    }

    static Value builtin_savePGM(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        ExpectArgsCount(args, 2, "savePGM");

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

        runtime.DefineFunction("setSeed", {this->fieldTypeInfo, integerTypeInfo}, builtin_setSeedFromInteger);
        runtime.DefineFunction("setSeed", {this->fieldTypeInfo, stringTypeInfo}, builtin_setSeedFromString);

        runtime.DefineIntrinsicFunction("fbmParameters", builtin_fbmParameters);
        runtime.DefineIntrinsicFunction("setNumberOfOctaves", builtin_setNumberOfOctaves);
        runtime.DefineIntrinsicFunction("setLacunarity", builtin_setLacunarity);
        runtime.DefineIntrinsicFunction("setPersistence", builtin_setPersistence);
        runtime.DefineIntrinsicFunction("setStartFrequency", builtin_setStartFrequency);
        runtime.DefineIntrinsicFunction("setNormalizeFBM", builtin_setNormalizeFBM);

        runtime.DefineIntrinsicFunction("field1", builtin_field1);
        runtime.DefineIntrinsicFunction("perlinNoise1", builtin_perlinNoise1);

        runtime.DefineIntrinsicFunction("savePGM", builtin_savePGM);
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
