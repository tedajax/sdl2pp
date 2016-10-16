#pragma once

#include <cstdint>

#include "pixels.h"

namespace sdl2 {


    struct DisplayMode {
        uint32_t m_format;
        int m_width;
        int m_height;
        int m_refreshRate;
        void* m_driverData;
    };
}