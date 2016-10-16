#pragma once

#include <string>
#include <array>
#include <functional>

#include "rect.h"
#include "video.h"

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
        WindowEventId m_eventId;
        int32_t m_data[2];
    };

    enum class HitTestResult {
        kNormal,
        kDraggable,
        kResizeTopLeft,
        kResizeTop,
        kResizeTopRight,
        kResizeRight,
        kResizeBottomRight,
        kResizeBottom,
        kResizeBottomLeft,
        kResizeLeft,
    };

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

        Window(const Window& other) = delete;
        Window(Window&& other);
        Window(void* windowPtr, bool isOwner) : m_window(windowPtr), m_isOwner(isOwner) {}
        Window(const char* title, int positionX, int positionY, int width, int height, WindowFlags flags);
        Window(const char* title, int width, int height, WindowFlags flags)
            : Window(title, kPositionCentered, kPositionCentered, width, height, flags) {}
        Window(const char* title, int width, int height)
            : Window(title, kPositionCentered, kPositionCentered, width, height, WindowFlags::kShown) {}

        ~Window();

        Window operator=(const Window& other) = delete;
        Window operator=(Window&& other) {
            m_window = other.m_window;
            other.m_window = nullptr;
        }

        template <typename T>
        T* get_ptr() const { return reinterpret_cast<T*>(m_window); }

        typedef std::array<uint16_t, 256> GammaRampChannel;
        typedef std::tuple<GammaRampChannel, GammaRampChannel, GammaRampChannel> GammaRamp;
        typedef std::function<HitTestResult(const Point&, void*)> HitTestFunc;
        typedef std::function<void(void*, void*, unsigned int, uint64_t, int64_t)> MessageHook;

        // return a tuple of <top, left, bottom, right>
        std::tuple<int, int, int, int> get_border_size() const;
        float get_brightness() const;
        void* get_data(const char* name) const;
        int get_display_index() const;
        DisplayMode get_display_mode() const;
        bool get_gamma_ramp(GammaRamp& dest) const;
        bool get_grab() const;
        uint32_t get_id() const;
        const Point get_max_size() const;
        const Point get_min_size() const;
        uint32_t get_pixel_format() const;
        float get_opacity() const;
        const Point get_position() const;
        const Point get_size() const;
        int get_width() const;
        int get_height() const;
        WindowFlags get_flags() const;
        const char* get_title() const;
        // Omitted because we need to create our represenation of Surface first
        //SDL_Surface* get_surface() const;
        // Omitted because it's not clear that it's necessary and the SysWMinfo struct is tough to reproduce
        //bool try_get_sys_wm_info(SDL_SysWMinfo* outInfo) const;

        void set_bordered(bool bordered);
        bool set_brightness(float brightness);
        void* set_data(const char* name, void* userData);
        bool set_display_mode(const DisplayMode& mode);
        bool set_fullscreen(WindowFlags flags);
        bool set_gamma_ramp(const GammaRamp& ramp);
        void set_grab(bool grabbed);
        bool set_hit_test(HitTestFunc callback, void* callbackData);
        //void set_icon(const Surface& surface);
        bool set_input_focus();
        void set_max_size(const Point& size);
        void set_min_size(const Point& size);
        //void set_modal_for(Window& parent); FIXME: 2.0.5
        bool set_opacity(float opacity);
        void set_position(const Point& position);
        void set_resizable(bool resizable);
        void set_size(const Point& size);
        void set_title(const char* title);

        static void set_message_hook(MessageHook callback, void* userData);

    private:
        void* m_window;
        bool m_isOwner;
        struct HitTestData {
            HitTestFunc m_callback = nullptr;
            void* m_data = nullptr;
        } m_hitTestData;
    };
}