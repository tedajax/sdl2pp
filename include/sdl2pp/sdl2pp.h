#pragma once

#include <cstdint>

#include "window.h"
#include "video.h"

namespace sdl2 {
    enum class SdlFlags : uint32_t {
        kNone = 0x00000000,
        kQuery = 0x00000000,
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

    class SdlContext {
    public:
        SdlContext(SdlFlags flags = SdlFlags::kInitEverything);
        ~SdlContext();

        bool init_subsystems(SdlFlags flags);
        void quit_subsystems(SdlFlags flags);
        bool query_systems(SdlFlags flags);
        SdlFlags get_init_systems();
    };
}