#pragma once

#include <cstdint>
#include "platform.h"

namespace sdl2 {
    constexpr uint32_t fourcc(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
        return (uint32_t)(a << 0) |
            (uint32_t)(b << 8) |
            (uint32_t)(c << 16) |
            (uint32_t)(d << 24);
    }

    FORCE_INLINE void memset4(void* dst, uint32_t val, size_t dwords);
    FORCE_INLINE void* memcpy4(void* dst, const void* src, size_t dwords);

    FORCE_INLINE float lerp(float a, float b, float t) {
        return a + (b - a) * t;
    }

    template <typename T>
    FORCE_INLINE T clamp(T v, T min, T max) {
        return (v < min) ? min : (v > max) ? max : v;
    }

    FORCE_INLINE float clamp01(float v) {
        return clamp(v, 0.f, 1.f);
    }
}
