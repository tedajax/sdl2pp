#include "platform.h"

#include <SDL2/SDL.h>

namespace sdl2 {
    const char* get_platform() {
        return SDL_GetPlatform();
    }
}