#include "IOModule.h"
#include "PDSL.h"
#include "PDSL_Utils.h"
#include "PGM.h"
#include "PLTypeInfo.h"

namespace Planeted
{
    static Value builtin_savePGM1(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "savePGM");
        std::string filename = GetStringArg(args, 1, "savePGM");
        AField1 &field1 = dynamic_cast<AField1&>(fieldValue.Get());

        filename = NormalizePath(runtime.OutPath + filename) + ".pgm";
        std::ofstream pgmfile(filename);
        pgmfile << PGM::Field1ToPGM(field1, 256);

        return Value::Null();
    }
    static Value builtin_savePGM2(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "savePGM");
        std::string filename = GetStringArg(args, 1, "savePGM");
        AField2 &field2 = dynamic_cast<AField2&>(fieldValue.Get());

        filename = NormalizePath(runtime.OutPath + filename) + ".pgm";
        std::ofstream pgmfile(filename);
        pgmfile << PGM::Field2ToPGM(field2, 256);

        return Value::Null();
    }
    static Value builtin_savePGM3(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        FieldValue fieldValue = GetFieldArg(args, 0, "savePGM");
        std::string filename = GetStringArg(args, 1, "savePGM");
        AField3 &field3 = dynamic_cast<AField3&>(fieldValue.Get());

        filename = NormalizePath(runtime.OutPath + filename) + ".pgm";
        std::ofstream pgmfile(filename);
        pgmfile << PGM::Field3ToPGM(field3, 256);

        return Value::Null();
    }

    IOModule::IOModule(PDSL_Runtime &runtime)
    {
        PLTypeInfo *field1TypeInfo = runtime.FieldsMod->GetField1TypeInfo();
        PLTypeInfo *field2TypeInfo = runtime.FieldsMod->GetField2TypeInfo();
        PLTypeInfo *field3TypeInfo = runtime.FieldsMod->GetField3TypeInfo();

        PLTypeInfo *stringTypeInfo = runtime.GetStringTypeInfo();

        runtime.DefineFunction("savePGM", {field1TypeInfo, stringTypeInfo}, builtin_savePGM1);
        runtime.DefineFunction("savePGM", {field2TypeInfo, stringTypeInfo}, builtin_savePGM2);
        runtime.DefineFunction("savePGM", {field3TypeInfo, stringTypeInfo}, builtin_savePGM3);
    }
}
