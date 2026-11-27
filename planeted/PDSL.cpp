#include "PDSL.h"

#include <memory>

#include "PDSL_Utils.h"
#include "PDSL_Parser.h"
#include "PLTypeUtils.h"

namespace Planeted
{
    static Value intrinsic_setDebugFlag(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        ExpectArgsCount(args, 1, "setDebugFlag");
        runtime.DebugFlag = args[0].GetBoolValue();
        return Value::Null();
    }
    static Value intrinsic_log(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        ExpectArgsCount(args, 1, "log");
        std::cout << args[0].ToString() << "\n";
        return Value::Null();
    }
    static Value intrinsic_load(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        ExpectArgsCount(args, 1, "load");
        return PDSL_Load(args[0].ToString(), runtime);
    }

    static Value intrinsic_typeof(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        ExpectArgsCount(args, 1, "typeof");
        if(args[0].IsNull())
        {
            throw std::runtime_error("argument of typeof cannot be null!");
        }

        PLTypeInfo *typeInfo = runtime.GetTypeInfo(args[0]);
        if(typeInfo == nullptr)
        {
            throw std::runtime_error("couldn't determine type of value: " + args[0].ToString());
        }
        return Value(typeInfo->ToString());
    }

    // move the below to floats and integer modules once they are available:
    static Value builtin_negateFloat(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        float operand = GetFloatArg(args, 0, OperatorsModule::NEGATE);

        return Value(-operand);
    }
    static Value builtin_negateInt(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        int operand = GetIntArg(args, 0, OperatorsModule::NEGATE);

        return Value(-operand);
    }


    static Value builtin_addFloats(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        float leftOp = GetFloatArg(args, 0, OperatorsModule::ADD);
        float rightOp = GetFloatArg(args, 1, OperatorsModule::ADD);

        return Value(leftOp + rightOp);
    }
    static Value builtin_addInts(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        int leftOp = GetIntArg(args, 0, OperatorsModule::ADD);
        int rightOp = GetIntArg(args, 1, OperatorsModule::ADD);

        return Value(leftOp + rightOp);
    }
    static Value builtin_mulFloats(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        float leftOp = GetFloatArg(args, 0, OperatorsModule::MULTIPLY);
        float rightOp = GetFloatArg(args, 1, OperatorsModule::MULTIPLY);

        return Value(leftOp * rightOp);
    }
    static Value builtin_mulInts(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        int leftOp = GetIntArg(args, 0, OperatorsModule::MULTIPLY);
        int rightOp = GetIntArg(args, 1, OperatorsModule::MULTIPLY);

        return Value(leftOp * rightOp);
    }

    // move the below to the string module, once that is available:
    static Value builtin_addStrings(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        std::string leftOp = GetStringArg(args, 0, OperatorsModule::ADD);
        std::string rightOp = GetStringArg(args, 1, OperatorsModule::ADD);

        return Value(leftOp + rightOp);
    }

    static Value intrinsic_toString(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        ExpectArgsCount(args, 1, "toString");
        return Value(args[0].ToString());
    }

    PDSL_Runtime::PDSL_Runtime()
    {
        this->OperatorsMod = std::make_unique<OperatorsModule>(*this);

        this->BooleansMod = std::make_unique<BooleansModule>(*this);

        this->booleanTypeInfo = this->DefineType("Boolean", ValueTypeEnum::Bool, nullptr);

        this->floatTypeInfo = this->DefineType("Float", ValueTypeEnum::Float, nullptr);
        this->integerTypeInfo = this->DefineType("Integer", ValueTypeEnum::Int, nullptr);
        this->listTypeInfo = this->DefineType("List", ValueTypeEnum::List, nullptr);
        this->stringTypeInfo = this->DefineType("String", ValueTypeEnum::String, nullptr);
        this->tupleTypeInfo = this->DefineType("Tuple", ValueTypeEnum::Tuple, nullptr);

        this->DefineFunction(OperatorsModule::NEGATE, {this->floatTypeInfo}, builtin_negateFloat);
        this->DefineFunction(OperatorsModule::NEGATE, {this->integerTypeInfo}, builtin_negateInt);

        this->DefineFunction(OperatorsModule::ADD, {this->floatTypeInfo, this->floatTypeInfo}, builtin_addFloats);
        this->DefineFunction(OperatorsModule::ADD, {this->integerTypeInfo, this->integerTypeInfo}, builtin_addInts);

        this->DefineFunction(OperatorsModule::MULTIPLY, {this->floatTypeInfo, this->floatTypeInfo}, builtin_mulFloats);
        this->DefineFunction(OperatorsModule::MULTIPLY, {this->integerTypeInfo, this->integerTypeInfo}, builtin_mulInts);

        this->DefineFunction(OperatorsModule::ADD, {this->stringTypeInfo, this->stringTypeInfo}, builtin_addStrings);
        this->DefineIntrinsicFunction("str", intrinsic_toString);

        this->DefineIntrinsicFunction("setDebugFlag", intrinsic_setDebugFlag);
        this->DefineIntrinsicFunction("log", intrinsic_log);
        this->DefineIntrinsicFunction("load", intrinsic_load);
        this->DefineIntrinsicFunction("typeof", intrinsic_typeof);

        this->FieldsMod = std::make_unique<FieldsModule>(*this);
        this->MeshMod = std::make_unique<MeshModule>(*this);
        this->IOMod = std::make_unique<IOModule>(*this);
    }

    PLTypeInfo *PDSL_Runtime::GetBooleanTypeInfo() const
    {
        return this->booleanTypeInfo;
    }

    PLTypeInfo *PDSL_Runtime::GetFloatTypeInfo() const
    {
        return this->floatTypeInfo;
    }
    PLTypeInfo *PDSL_Runtime::GetIntegerTypeInfo() const
    {
        return this->integerTypeInfo;
    }
    PLTypeInfo *PDSL_Runtime::GetListTypeInfo() const
    {
        return this->listTypeInfo;
    }
    PLTypeInfo *PDSL_Runtime::GetStringTypeInfo() const
    {
        return this->stringTypeInfo;
    }
    PLTypeInfo *PDSL_Runtime::GetTupleTypeInfo() const
    {
        return this->tupleTypeInfo;
    }

    PLTypeInfo *PDSL_Runtime::DefineType(std::string name, ValueTypeEnum valueType, PLTypeInfo *baseType)
    {
        PLTypeInfo *result = new PLTypeInfo(name, valueType, baseType);

        this->typeInfoTable[name] = result;

        return result;
    }

    PLTypeInfo *PDSL_Runtime::FindType(std::string name) const
    {
        PLTypeInfo *result = nullptr;

        std::unordered_map<std::string, PLTypeInfo*>::const_iterator it = this->typeInfoTable.find(name);
        if(it != this->typeInfoTable.end())
        {
            result = it->second;
        }
        return result;
    }

    PLTypeInfo *PDSL_Runtime::GetTypeInfo(const Value &value) const
    {
        PLTypeInfo *result = nullptr;

        switch(value.GetValueType())
        {
        case ValueTypeEnum::Bool:
            return this->GetBooleanTypeInfo();
            break;
        case ValueTypeEnum::FBMParameters:
            return this->FieldsMod->GetFBMParametersTypeInfo();
            break;
        case ValueTypeEnum::Field:
            {
                FieldValue fieldValue;
                if(TryAsField(value, fieldValue))
                {
                    result = fieldValue.GetTypeInfo(*this);
                }
            }
            break;
        case ValueTypeEnum::Float:
            return this->GetFloatTypeInfo();
            break;
        case ValueTypeEnum::Int:
            return this->GetIntegerTypeInfo();
            break;
        case ValueTypeEnum::List:
            return this->GetListTypeInfo();
            break;
        case ValueTypeEnum::Mesh:
            return this->MeshMod->GetMeshTypeInfo();
            break;
        case ValueTypeEnum::String:
            result = this->GetStringTypeInfo();
            break;
        case ValueTypeEnum::Tuple:
            result = this->GetTupleTypeInfo();
            break;
        default:
            break;
        }
        return result;
    }

    Value PDSL_Runtime::GetVariableValue(const std::string &name) const
    {
        std::unordered_map<std::string, Value>::const_iterator it = this->environment.find(name);
        if(it == this->environment.end())
        {
            throw std::runtime_error("Undefined variable: " + name);
        }
        return it->second;
    }
    void PDSL_Runtime::SetVariableValue(std::string name, Value value)
    {
        this->environment[name] = value;
    }

    void PDSL_Runtime::DefineIntrinsicFunction(std::string name, BuiltinFunction::BuiltinFunctionPtr fn)
    {
        this->intrinsicFunctionsTable[name] = fn;
    }

    void PDSL_Runtime::DefineFunction(std::string name, const std::vector<PLTypeInfo*> &argumentTypes, BuiltinFunction::BuiltinFunctionPtr fn)
    {
        this->functionsTable[name].push_back(std::make_unique<BuiltinFunction>(name, argumentTypes, fn));
    }
    Value PDSL_Runtime::CallFunction(std::string &name, std::vector<Value> &args)
    {
        // try intrinsics first:
        auto it = this->intrinsicFunctionsTable.find(name);
        if(it != this->intrinsicFunctionsTable.end())
        {
            return it->second(*this, args);
        }

        // try other functions:
        AFunction *fn = this->findMatchingFunction(name, args);

        if(fn == nullptr)
        {
            throw std::runtime_error("Unknown function: " + name +
                                     "(" + PLTypeUtils::TypeInfoListToString(PLTypeUtils::ResolveTypes(*this, args))+")");
        }
        return fn->Call(*this, args);
    }

    AFunction *PDSL_Runtime::findMatchingFunction(const std::string &name, const std::vector<Value> &arguments)
    {
        auto it = this->functionsTable.find(name);

        if (it == this->functionsTable.end())
        {
            return nullptr;
        }

        for (auto &fn : it->second)
        {
            if (fn->Matches(*this, arguments))
            {
                return fn.get();
            }
        }
        return nullptr;
    }

    void PDSL_Runtime::DumpEnvironment()
    {
        std::cout << "environment: \n";
        for(auto &v : this->environment)
        {
            std::cout << v.first << "\n";
        }
    }

    std::string PDSL_Runtime::ResolvePath(const std::string &filename) const
    {
        std::string current;

        if (!this->FileStack.empty())
        {
            current = FileStack.back();
        }

        // If no current file, treat as working directory case
        if (current.empty())
        {
            return filename;
        }

        // strip file name keep directory
        size_t pos = current.find_last_of("/\\");
        std::string dir = (pos == std::string::npos) ? "" : current.substr(0, pos + 1);

        return NormalizePath(dir + filename);
    }

    static void run(const Program &program, PDSL_Runtime &runtime)
    {
        for(const std::unique_ptr<Statement> &stmt : program.statements)
        {
            stmt->execute(runtime);
        }
    }

    void PDSL_Run(const std::string &code, PDSL_Runtime &runtime)
    {
        Lexer lexer(code);
        Parser parser(lexer);
        Program program = parser.Parse();
        run(program, runtime);
    }

    void PDSL_RunFile(const std::string &filename, PDSL_Runtime &runtime)
    {
        std::string resolved = runtime.ResolvePath(filename);
        std::cout << "running file: " << resolved << "\n";

        runtime.FileStack.push_back(resolved);

        PDSL_Run(ReadFile(resolved), runtime);

        if(runtime.DebugFlag)
        {
            runtime.DumpEnvironment();
        }

        runtime.FileStack.pop_back();
    }

    Value PDSL_Load(const std::string &filename, PDSL_Runtime &runtime)
    {
        PDSL_Runtime new_runtime;

        new_runtime.OutPath = runtime.OutPath;

        PDSL_RunFile(runtime.ResolvePath(filename), new_runtime);

        return new_runtime.Result;
    }
}
