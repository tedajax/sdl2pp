#pragma once

#include "pixels.h"

namespace sdl2 {
    class Surface {
        template <typename T>
        T* get_ptr() { return reinterpret_cast<T*>(m_surface); }
    private:
        void* m_surface;
    };
}