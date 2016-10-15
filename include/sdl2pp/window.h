#pragma once

#include <string>

namespace sdl2 {
    enum class WindowEventId {
        kNone,
        kShown,
        kHidden,
        kExposed,
        kMoved,
        kResized,
        kSizeChanged,
        kMinimized,
        kMaximized,
        kRestored,
        kEnter,
        kLeave,
        kFocusGained,
        kFocusLost,
        kClose,
    };

    struct WindowEvent {
        WindowEventId 
    }

    enum class WindowFlags : uint32_t {
        kFullscreen = 0x00000001,
        kOpenGl = 0x00000002,
        kShown = 0x00000004,
        kHidden = 0x00000008,
        kBorderless = 0x00000010,
        kResizable = 0x00000020,
        kMinimized = 0x00000040,
        kMaximized = 0x00000080,
        kInputGrabbed = 0x00000100,
        kInputFocus = 0x00000200,
        kMouseFocus = 0x00000400,
        kFullscreenDesktop = (kFullscreen | 0x00001000),
        kForeign = 0x00000800,
        kAllowHighDpi = 0x00002000,
        kMouseCapture = 0x00004000,
    };

    class Window {
    public:
        static const int kPositionUndefined = 0x1FFF0000;
        static const int kPositionCentered = 0x2FFF0000;

        Window(const char* title, int positionX, int positionY, int width, int height, WindowFlags flags);
        Window(const char* title, int width, int height, WindowFlags flags)
            : Window(title, kPositionCentered, kPositionCentered, width, height, flags) {}
        Window(const char* title, int width, int height)
            : Window(title, kPositionCentered, kPositionCentered, width, height, WindowFlags::kShown) {}

        ~Window();

        const char* get_title() const { return m_title.c_str(); }
        const int get_position_x() const { return m_positionX; }
        const int get_position_y() const { return m_positionY; }

    private:
        SDL_Window* m_window;
        std::string m_title;
        int m_positionX;
        int m_positionY;
        int m_width;
        int m_height;
        WindowFlags m_flags;
    };
}