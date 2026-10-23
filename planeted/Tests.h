#ifndef PLANETED_TESTS_H
#define PLANETED_TESTS_H

#include "Noise.h"
#include "Random.h"

namespace Planeted
{
    void NoiseTest1D(const std::string &filename, const ANoise &noise);
    void NoiseTest2D(const std::string &filename, const ANoise &noise);
    void NoiseTest3D(const std::string &filename, const ANoise &noise);
}
#endif
