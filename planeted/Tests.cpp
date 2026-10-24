#include "Tests.h"

#include <fstream>

#include "PixelMap.h"
#include "PPM.h"
#include "PGM.h"

namespace Planeted
{
    static uint16_t sample_size = 256;

    static std::uint8_t NoiseToGrayScale(float noise)
    {
        return ToUint8(SignedToUnitRange(noise));
    }

    static void noiseTest(const std::string &filename, ColorFunction fn)
    {
        PixelMap pixMap = PixelMap(sample_size, sample_size);

        pixMap.FillRect(0, 0, sample_size, sample_size, fn);

        std::ofstream pgmfile(filename + ".pgm");

        pgmfile << PGM::PixelMapToPGM(pixMap);
    }

    static ColorFunction ToColorFunction1D(const ANoise &noise)
    {
        return [&noise](const int x, const int y)
        {
            float nx = x/static_cast<float>(sample_size) - 0.5f;
            return NoiseToGrayScale(noise.Eval(nx));
        };
    }
    static ColorFunction ToColorFunction2D(const ANoise &noise)
    {
        return [&noise](const int x, const int y)
        {
            float nx = x/static_cast<float>(sample_size) - 0.5f;
            float ny = y/static_cast<float>(sample_size) - 0.5f;
            return NoiseToGrayScale(noise.Eval({nx, ny}));
        };
    }
    static ColorFunction ToColorFunction3D(const ANoise &noise)
    {
        return [&noise](const int x, const int y)
        {
            float nx = x/static_cast<float>(sample_size) - 0.5f;
            float ny = y/static_cast<float>(sample_size) - 0.5f;
            return NoiseToGrayScale(noise.Eval({nx, ny, 1.0f}));
        };
    }
    void NoiseTest1D(const std::string &filename, const ANoise &noise)
    {
        ColorFunction fn = ToColorFunction1D(noise);
        noiseTest(filename, fn);
    }
    void NoiseTest2D(const std::string &filename, const ANoise &noise)
    {
        ColorFunction fn = ToColorFunction2D(noise);
        noiseTest(filename, fn);
    }
    void NoiseTest3D(const std::string &filename, const ANoise &noise)
    {
        ColorFunction fn = ToColorFunction3D(noise);
        noiseTest(filename, fn);
    }
}
