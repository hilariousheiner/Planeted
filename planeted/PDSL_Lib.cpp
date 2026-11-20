#include "PDSL_Lib.h"

#include <memory>
#include <iostream>

#include "Math.h"
#include "Noise.h"
#include "PerlinNoise.h"
#include "PDSL_Utils.h"
#include "PGM.h"
#include "PixelMap.h"
#include "ValueNoise.h"
#include "WhiteNoise.h"

namespace Planeted
{
    namespace PDSL_Lib
    {
        static Value builtin_subdivide(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "subdivide");

            Mesh m = GetMeshArg(args, 0, "subdivide");
            int d = GetIntArg(args, 1, "subdivide");

            m.Subdivide(d);

            return Value(m);
        }
        static Value builtin_tessellate(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "tessellate");

            Mesh m = GetMeshArg(args, 0, "tessellate");
            int n = args[1].GetIntValue();

            m.Tessellate(n);

            return Value(m);
        }
        static Value builtin_projectToUnitSphere(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "projectToUnitSphere");

            Mesh m = GetMeshArg(args, 0, "projectToUnitSphere");
            m.ProjectToUnitSphere();

            return Value(m);
        }
        static Value builtin_calculateNormals(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "calculateNormals");

            Mesh m = GetMeshArg(args, 0, "calculateNormals");
            m.CalculateNormals();

            return Value(m);
        }

        void Load(PDSL_Runtime &runtime)
        {
            runtime.DefineIntrinsicFunction("subdivide", builtin_subdivide);
            runtime.DefineIntrinsicFunction("tessellate", builtin_tessellate);
            runtime.DefineIntrinsicFunction("projectToUnitSphere", builtin_projectToUnitSphere);
            runtime.DefineIntrinsicFunction("calculateNormals", builtin_calculateNormals);
        }
    }
}
