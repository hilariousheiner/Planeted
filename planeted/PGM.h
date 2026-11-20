#ifndef PLANETED_PBM_H
#define PLANETED_PBM_H

#include <sstream>
#include <string.h>
#include <vector>

#include "Field.h"
#include "PixelMap.h"

namespace Planeted
{
    namespace PGM
    {
        std::string Field1ToPGM(const AField1 &field1, uint16_t sample_size);
        std::string Field2ToPGM(const AField2 &field2, uint16_t sample_size);
        std::string Field3ToPGM(const AField3 &field3, uint16_t sample_size);

        std::string PixelMapToPGM(const PixelMap &pmap);
    }
}
#endif
