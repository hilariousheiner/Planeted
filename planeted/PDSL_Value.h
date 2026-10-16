#ifndef PLANETED_PDSL_VALUE_H
#define PLANETED_PDSL_VALUE_H

#include <memory>
#include <variant>
#include <vector>

#include "Mesh.h"
#include "NoiseFunction.h"

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
        Noise
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

    class NoiseValue
    {
    public:
        NoiseValue() = default;

        explicit NoiseValue(std::unique_ptr<NoiseFunction> noise)
            : noise(std::move(noise))
        {}

        NoiseValue(const NoiseValue &other)
            : noise(other.noise->Clone())
        {}

        NoiseValue &operator=(const NoiseValue &other)
        {
            if(this != &other)
            {
                this->noise = other.noise->Clone();
            }
            return *this;
        }

        NoiseValue(NoiseValue&&) noexcept = default;
        NoiseValue& operator=(NoiseValue&&) noexcept = default;

        NoiseFunction &Get()
        {
            return *noise;
        }

    private:
        std::unique_ptr<NoiseFunction> noise;
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

        bool IsNull() const;
        static const Value &Null();

        int GetIntValue() const;
        float GetFloatValue() const;
        bool GetBoolValue() const;
        std::string GetStringValue() const;

        const Tuple &GetTupleValue() const;
        const List &GetListValue() const;

        const Mesh &GetMeshValue() const;
        const NoiseValue &GetNoiseValue() const;

        ValueTypeEnum GetValueType() const;

        std::string ToString() const;
        std::string TypeToString() const;

    private:
        std::variant<std::monostate, int, float, bool, std::string, Tuple, List, Mesh, NoiseValue> data;
    };
}
#endif // PLANETED_PDSL_VALUE_H
