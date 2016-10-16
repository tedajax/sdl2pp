#include "stdinc.h"

#include <SDL2/SDL.h>

namespace sdl2 {
    FORCE_INLINE void memset4(void* dst, uint32_t val, size_t dwords) {
        SDL_memset4(dst, val, dwords);
    }

    FORCE_INLINE void* memcpy4(void* dst, const void* src, size_t dwords) {
        return SDL_memcpy4(dst, src, dwords);
    }
}