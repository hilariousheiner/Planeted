#ifndef PLANETED_FIELD_H
#define PLANETED_FIELD_H

#include <memory>

#include "ISeedable.h"
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
}
#endif // PLANETED_FIELD_H
