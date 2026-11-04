#ifndef PLANETED_VALUETYPEENUM_H
#define PLANETED_VALUETYPEENUM_H

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
        Field
    };
}
#endif // PLANETED_VALUETYPEENUM_H
