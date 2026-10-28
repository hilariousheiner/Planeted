#ifndef PLANETED_FIELD_H
#define PLANETED_FIELD_H

#include <memory>

#include "ISeedable.h"
#include "Seed.h"
#include "Vector2.h"
#include "Vector3.h"

namespace Planeted
{
    class IField1 : public ISeedable
    {
    public:
        virtual ~IField1() = default;
        virtual std::unique_ptr<IField1> Clone() const = 0;

        virtual float Eval(const float &p) const = 0;
    };

    class IField2 : public ISeedable
    {
    public:
        virtual ~IField2() = default;
        virtual std::unique_ptr<IField2> Clone() const = 0;

        virtual float Eval(const Vector2 &p) const = 0;
    };

    class IField3 : public ISeedable
    {
    public:
        virtual ~IField3() = default;
        virtual std::unique_ptr<IField3> Clone() const = 0;

        virtual float Eval(const Vector3 &p) const = 0;
    };

    class AFieldGenerator1 : public IField1
    {
    public:
        void SetSeed(std::uint32_t seedValue) override;
        void SetSeed(std::string seedValue) override;

    protected:
        Seed seed;
    };

    class AFieldGenerator2 : public IField2
    {
    public:
        void SetSeed(std::uint32_t seedValue) override;
        void SetSeed(std::string seedValue) override;

    protected:
        Seed seed;
    };

    class AFieldGenerator3 : public IField3
    {
    public:
        void SetSeed(std::uint32_t seedValue) override;
        void SetSeed(std::string seedValue) override;

    protected:
        Seed seed;
    };

    class AbsFieldModifier1 : public IField1
    {
    public:
        AbsFieldModifier1(std::unique_ptr<IField1> field);
        AbsFieldModifier1(const AbsFieldModifier1 &other);

        std::unique_ptr<IField1> Clone() const override;

        float Eval(const float &p) const override;

        void SetSeed(std::uint32_t seed) override;
        void SetSeed(std::string seed) override;

    private:
        std::unique_ptr<IField1> field;
    };
}
#endif // PLANETED_FIELD_H
