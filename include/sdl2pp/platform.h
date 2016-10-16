#pragma once

#ifndef FORCE_INLINE
#if defined(_MSC_VER)
#define FORCE_INLINE __forceinline
#elif ( (defined(__GNUC__) && (__GNUC__ >= 4)) || defined(__clang__) )
#define FORCE_INLINE __attribute__((always_inline)) static __inline__
#else
#define FORCE_INLINE static SDL_INLINE
#endif
#endif /* FORCE_INLINE not defined */

namespace sdl2 {
    static const char* get_platform();
}