#ifndef PLANETED_PDSL_VALUE_H
#define PLANETED_PDSL_VALUE_H

#include <memory>
#include <variant>
#include <vector>

#include "Mesh.h"
#include "FBM.h"
#include "Field.h"
#include "FieldValue.h"
#include "Noise.h"
#include "NoiseValue.h"

namespace Planeted
{
    enum class ValueTypeEnum
    {
        Int,
        Float,
        Bool,
        String,
        Null,

        Tuple,
        List,

        Mesh,
        Noise,
        FBMParameters,
        Field1
    };

    class Value;

    struct Tuple
    {
        std::vector<Value> elements;

        std::string ToString() const;
    };

    struct List
    {
        std::vector<Value> elements;

        std::string ToString() const;
    };

    class Value
    {
    public:
        Value();
        explicit Value(int intValue);
        explicit Value(float floatValue);
        explicit Value(bool boolValue);
        explicit Value(std::string stringValue);

        explicit Value(Tuple tupleValue);
        explicit Value(List listValue);
        explicit Value(Mesh meshValue);

        explicit Value(NoiseValue noiseValue);
        explicit Value(FBMParameters fbmParametersValue);

        explicit Value(Field1Value field1Value);

        bool IsNull() const;
        static const Value &Null();

        int GetIntValue() const;
        float GetFloatValue() const;
        bool GetBoolValue() const;
        std::string GetStringValue() const;

        const Tuple &GetTupleValue() const;
        const List &GetListValue() const;

        const Mesh &GetMeshValue() const;

        const FBMParameters &GetFBMParametersValue() const;

        const NoiseValue &GetNoiseValue() const;
        const Field1Value &GetField1Value() const;

        ValueTypeEnum GetValueType() const;

        std::string ToString() const;
        std::string TypeToString() const;

    private:
        std::variant<std::monostate, int, float, bool, std::string, Tuple, List, Mesh, NoiseValue, FBMParameters, Field1Value> data;
    };
}
#endif // PLANETED_PDSL_VALUE_H
