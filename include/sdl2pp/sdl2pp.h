#pragma once

#include <cstdint>

#include "window.h"

namespace sdl2 {
    enum class SdlFlags : uint32_t {
        kInitTimer = 0x00000001,
        kInitAudio = 0x00000010,
        kInitVideo = 0x00000020,
        kInitJoystick = 0x00000200,
        kInitHaptic = 0x00001000,
        kInitGameController = 0x00002000,
        kInitEvents = 0x00004000,
        kInitNoParachute = 0x00100000,
        kInitEverything = 0x00107231,
    };

    class Sdl {
    public:
        Sdl(sdl_flags flags = SdlFlags::kInitEverything);
        ~Sdl();

        bool init_subsystem(sdl_flags flags);
        void quit_subsystem(sdl_flags flags);
        bool was_init(sdl_flags flags);
    };
}