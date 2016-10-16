#pragma once

#include <cstdint>

namespace sdl2 {
    struct Version {
        uint8_t m_major = 0, m_minor = 0, m_patch = 0;
    };

    enum class SysWmType {
        kUnknown,
        kWindows,
        kX11,
        kDirectFb,
        kCocoa,
        kUiKit,
        kWayland,
        kMir,
        kWinRt,
        kAndroid,
        KVivante
    };
}