#include "PDSL.h"

#include <memory>

#include "PDSL_Lib.h"
#include "PDSL_Utils.h"
#include "PDSL_Parser.h"

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

    PDSL_Runtime::PDSL_Runtime()
    {
        this->booleanTypeInfo = this->DefineType("Boolean", ValueTypeEnum::Bool, nullptr);
        this->fbmParametersTypeInfo = this->DefineType("FBMParamters", ValueTypeEnum::FBMParameters, nullptr);
        this->fieldTypeInfo = this->DefineType("Field", ValueTypeEnum::Field, nullptr);
        this->floatTypeInfo = this->DefineType("Float", ValueTypeEnum::Float, nullptr);
        this->integerTypeInfo = this->DefineType("Integer", ValueTypeEnum::Int, nullptr);
        this->listTypeInfo = this->DefineType("List", ValueTypeEnum::List, nullptr);
        this->meshTypeInfo = this->DefineType("Mesh", ValueTypeEnum::Mesh, nullptr);
        this->noiseTypeInfo = this->DefineType("Noise", ValueTypeEnum::Noise, nullptr);
        this->stringTypeInfo = this->DefineType("String", ValueTypeEnum::String, nullptr);
        this->tupleTypeInfo = this->DefineType("Tuple", ValueTypeEnum::Tuple, nullptr);

        this->DefineIntrinsicFunction("setDebugFlag", intrinsic_setDebugFlag);
        this->DefineIntrinsicFunction("log", intrinsic_log);
        this->DefineIntrinsicFunction("load", intrinsic_load);
        this->DefineIntrinsicFunction("typeof", intrinsic_typeof);
    }

    PLTypeInfo *PDSL_Runtime::GetBooleanTypeInfo() const
    {
        return this->booleanTypeInfo;
    }
    PLTypeInfo *PDSL_Runtime::GetFBMParametersTypeInfo() const
    {
        return this->fbmParametersTypeInfo;
    }
    PLTypeInfo *PDSL_Runtime::GetFieldTypeInfo() const
    {
        return this->fieldTypeInfo;
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
    PLTypeInfo *PDSL_Runtime::GetMeshTypeInfo() const
    {
        return this->meshTypeInfo;
    }
    PLTypeInfo *PDSL_Runtime::GetNoiseTypeInfo() const
    {
        return this->noiseTypeInfo;
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
            return this->GetFBMParametersTypeInfo();
            break;
        case ValueTypeEnum::Field:
            return this->GetFieldTypeInfo();
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
            return this->GetMeshTypeInfo();
            break;
        case ValueTypeEnum::Noise:
            return this->GetNoiseTypeInfo();
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
            throw std::runtime_error("Unknown function: " + name);
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

        PDSL_Lib::Load(new_runtime);

        new_runtime.OutPath = runtime.OutPath;

        PDSL_RunFile(runtime.ResolvePath(filename), new_runtime);

        return new_runtime.Result;
    }
}
