#ifndef PLANETED_TESTS_H
#define PLANETED_TESTS_H

#include "Noise.h"
#include "Random.h"

namespace Planeted
{
    void NoiseTest1D(const std::string &filename, Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseFunction1D noiseFun);
    void NoiseTest2D(const std::string &filename, Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseFunction2D noiseFun);
    void NoiseTest3D(const std::string &filename, Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseFunction3D noiseFun);

    void NoiseTest1D(const std::string &filename, const ANoise &noise);
    void NoiseTest2D(const std::string &filename, const ANoise &noise);
    void NoiseTest3D(const std::string &filename, const ANoise &noise);
}
#endif
