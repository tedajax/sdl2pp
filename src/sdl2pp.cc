#include <SDL2/SDL.h>

#include "sdl2pp.h"

namespace sdl2 {

    SdlContext::SdlContext(SdlFlags flags /* = SdlFlags::kInitEverything */) {
        SDL_Init((uint32_t)flags);
    }

    SdlContext::~SdlContext() {
        SDL_Quit();
    }

    bool SdlContext::init_subsystems(SdlFlags flags) {
        return SDL_InitSubSystem((uint32_t)flags);
    }

    void SdlContext::quit_subsystems(SdlFlags flags) {
        SDL_QuitSubSystem((uint32_t)flags);
    }

    bool SdlContext::query_systems(SdlFlags flags) {
        return SDL_WasInit((uint32_t)flags) == (uint32_t)flags;
    }

    SdlFlags SdlContext::get_init_systems() {
        return (SdlFlags)SDL_WasInit(0);
    }
}