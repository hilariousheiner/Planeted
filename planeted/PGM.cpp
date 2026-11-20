#include "PGM.h"
#include "Math.h"

namespace Planeted
{
    namespace PGM
    {
        std::string Field1ToPGM(const AField1 &field1, uint16_t sample_size)
        {
            std::stringstream stream;

            stream << "P2\n";
            stream << sample_size << " " << sample_size << "\n";
            stream << "255\n";

            for(int y = 0; y < sample_size; y++)
            {
                for(int x = 0; x < sample_size; x++)
                {
                    float nx = x/static_cast<float>(sample_size) - 0.5f;
                    std::uint8_t c = ToUint8(SignedToUnitRange(field1.Eval(nx)));

                    stream << static_cast<int>(c) << "\n";
                }
            }
            return stream.str();
        }

        std::string Field2ToPGM(const AField2 &field2, uint16_t sample_size)
        {
            std::stringstream stream;

            stream << "P2\n";
            stream << sample_size << " " << sample_size << "\n";
            stream << "255\n";

            for(int y = 0; y < sample_size; y++)
            {
                for(int x = 0; x < sample_size; x++)
                {
                    float nx = x/static_cast<float>(sample_size) - 0.5f;
                    float ny = y/static_cast<float>(sample_size) - 0.5f;
                    std::uint8_t c = ToUint8(SignedToUnitRange(field2.Eval({nx, ny})));

                    stream << static_cast<int>(c) << "\n";
                }
            }
            return stream.str();
        }

        std::string Field3ToPGM(const AField3 &field3, uint16_t sample_size)
        {
            std::stringstream stream;

            stream << "P2\n";
            stream << sample_size << " " << sample_size << "\n";
            stream << "255\n";

            for(int y = 0; y < sample_size; y++)
            {
                for(int x = 0; x < sample_size; x++)
                {
                    float nx = x/static_cast<float>(sample_size) - 0.5f;
                    float ny = y/static_cast<float>(sample_size) - 0.5f;
                    std::uint8_t c = ToUint8(SignedToUnitRange(field3.Eval({nx, ny, 1.0f})));

                    stream << static_cast<int>(c) << "\n";
                }
            }
            return stream.str();
        }

        std::string PixelMapToPGM(const PixelMap &pmap)
        {
            std::stringstream stream;

            int width = pmap.GetWidth();
            int height = pmap.GetHeight();
            const std::vector<Color>& data = pmap.GetData();

            stream << "P2\n";
            stream << width << " " << height << "\n";
            stream << "255\n";

            for (const Color &pixel : data)
            {
                stream << static_cast<int>(pixel.R) << "\n";
            }
            return stream.str();
        }
    }
}
