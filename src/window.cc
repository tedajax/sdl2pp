#include <SDL2/SDL.h>

#include "assert.h"
#include "window.h"

namespace sdl2 {
    Window::Window(const char* title, int positionX, int positionY, int width, int height, WindowFlags flags)
        : m_title(title),
        m_positionX(positionX), m_positionY(positionY),
        m_width(width), m_height(height),
        m_flags(flags),
        m_window(nullptr)
    {
        m_window = SDL_CreateWindow(title, positionX, positionY, width, height, (Uint32)flags);
        ASSERT(m_window, "Unable to create window.");
    }

    Window::~Window() {
        if (m_window) {
            SDL_DestroyWindow(m_window);
        }
    }
}