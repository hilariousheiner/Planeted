#ifndef PLANETED_PDSL_H
#define PLANETED_PDSL_H

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>


#include "BuiltinFunction.h"
#include "Utils.h"

#include "PDSL_Lexer.h"
#include "PDSL_Token.h"
#include "PDSL_Value.h"

/*
 * PDSL = planeted scripting language
 */

namespace Planeted
{
    struct PDSL_Runtime;

    void PDSL_Run(const std::string &code, PDSL_Runtime &runtime);
    void PDSL_RunFile(const std::string &filename, PDSL_Runtime &runtime);

    Value PDSL_Load(const std::string &filename, PDSL_Runtime &runtime);

    struct PDSL_Runtime
    {
        PDSL_Runtime();

        PLTypeInfo *DefineType(std::string name, ValueTypeEnum valueType, PLTypeInfo *baseType);
        PLTypeInfo *FindType(std::string name) const;
        PLTypeInfo *GetTypeInfo(const Value &value) const;

        PLTypeInfo *GetBooleanTypeInfo() const;
        PLTypeInfo *GetFBMParatersTypeInfo() const;
        PLTypeInfo *GetFieldTypeInfo() const;
        PLTypeInfo *GetFloatTypeInfo() const;
        PLTypeInfo *GetIntegerTypeInfo() const;
        PLTypeInfo *GetListTypeInfo() const;
        PLTypeInfo *GetMeshTypeInfo() const;
        PLTypeInfo *GetNoiseTypeInfo() const;
        PLTypeInfo *GetStringTypeInfo() const;
        PLTypeInfo *GetTupleTypeInfo() const;

        Value GetVariableValue(const std::string &name) const;
        void SetVariableValue(std::string name, Value value);

        void DefineIntrinsicFunction(std::string name, BuiltinFunction::BuiltinFunctionPtr fn);
        void DefineFunction(std::string name, const std::vector<PLTypeInfo*> &argumentTypes, BuiltinFunction::BuiltinFunctionPtr fn);
        Value CallFunction(std::string &name, std::vector<Value> &args);

        void DumpEnvironment();

        std::string ResolvePath(const std::string &filename) const;

        std::vector<std::string> FileStack;

        std::string OutPath;

        Value Result;
        bool DebugFlag = false;

    private:
        std::unordered_map<std::string, PLTypeInfo*> typeInfoTable;

        PLTypeInfo *booleanTypeInfo;
        PLTypeInfo *fbmParametersTypeInfo;
        PLTypeInfo *fieldTypeInfo;
        PLTypeInfo *floatTypeInfo;
        PLTypeInfo *integerTypeInfo;
        PLTypeInfo *listTypeInfo;
        PLTypeInfo *meshTypeInfo;
        PLTypeInfo *noiseTypeInfo;
        PLTypeInfo *stringTypeInfo;
        PLTypeInfo *tupleTypeInfo;

        std::unordered_map<std::string, Value> environment;

        std::unordered_map<std::string, BuiltinFunction::BuiltinFunctionPtr> intrinsicFunctionsTable;
        std::unordered_map<std::string, std::vector<std::unique_ptr<AFunction>>> functionsTable;
        AFunction *findMatchingFunction(const std::string &name, const std::vector<Value> &arguments);
    };
}
#endif
