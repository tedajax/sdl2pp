#include "assert.h"
#include "window.h"

#include <SDL2/SDL.h>

namespace sdl2 {
    namespace internal {
        struct MessageHookData {
            Window::MessageHook m_callback;
            void* m_data;
        };
        static MessageHookData s_messageHookData;
    }

    Window::Window(Window&& other)
        : m_window(other.get_ptr<void>()),
        m_isOwner(other.m_isOwner) {
        other.m_window = nullptr;
        set_hit_test(other.m_hitTestData.m_callback, other.m_hitTestData.m_data);
    }

    Window::Window(const char* title, int positionX, int positionY, int width, int height, WindowFlags flags)
        : m_window(nullptr),
        m_isOwner(true)
    {
        m_window = SDL_CreateWindow(title, positionX, positionY, width, height, (Uint32)flags);
        ASSERT(m_window, "Unable to create window.");
    }

    Window::~Window() {
        if (m_window && m_isOwner) {
            SDL_DestroyWindow(get_ptr<SDL_Window>());
        }
    }

    std::tuple<int, int, int, int> Window::get_border_size() const {
        int left = 0, right = 0, top = 0, bottom = 0;
        #if 0 // FIXME: Not available until SDL 2.0.5
        SDL_GetWindowBorderSize(get_ptr<SDL_Window>(), &top, &left, &right, bottom);
        #endif
        return { top, left, right, bottom };
    }

    float Window::get_brightness() const {
        return SDL_GetWindowBrightness(get_ptr<SDL_Window>());
    }

    // void* Window::get_window_data(const char* name) const {
    //     return SDL_GetWindowData(get_ptr<SDL_Window>(), name);
    // }

    int Window::get_display_index() const {
        return SDL_GetWindowDisplayIndex(get_ptr<SDL_Window>());
    }

    namespace display_mode {
        static DisplayMode from_sdl(SDL_DisplayMode* mode) {
            DisplayMode result = {
                mode->format,
                mode->w, mode->h,
                mode->refresh_rate,
                mode->driverdata,
            };
            return result;
        }
    }

    DisplayMode Window::get_display_mode() const {
        SDL_DisplayMode displayMode;
        SDL_GetWindowDisplayMode(get_ptr<SDL_Window>(), &displayMode);
        return sdl2::display_mode::from_sdl(&displayMode);
    }

    bool Window::get_gamma_ramp(GammaRamp& dest) const {
        return SDL_GetWindowGammaRamp(get_ptr<SDL_Window>(),
            &std::get<0>(dest)[0],
            &std::get<1>(dest)[0],
            &std::get<2>(dest)[0]) == 0;
    }

    bool Window::get_grab() const {
        return SDL_GetWindowGrab(get_ptr<SDL_Window>()) == SDL_TRUE;
    }

    uint32_t Window::get_id() const {
        return SDL_GetWindowID(get_ptr<SDL_Window>());
    }

    const Point Window::get_max_size() const {
        Point result;
        SDL_GetWindowMaximumSize(get_ptr<SDL_Window>(), &result[0], &result[1]);
        return result;
    }

    const Point Window::get_min_size() const {
        Point result;
        SDL_GetWindowMinimumSize(get_ptr<SDL_Window>(), &result[0], &result[1]);
        return result;
    }

    float Window::get_opacity() const {
        float result = 1.f;
        // FIXME: wait for 2.0.5 upgrade
        //SDL_GetWindowOpacity(get_ptr<SDL_Window>(), &result);
        return result;
    }

    uint32_t Window::get_pixel_format() const {
        return SDL_GetWindowPixelFormat(get_ptr<SDL_Window>());
    }

    const Point Window::get_position() const {
        Point result;
        SDL_GetWindowPosition(get_ptr<SDL_Window>(), &result[0], &result[1]);
        return result;
    }

    const Point Window::get_size() const {
        Point result;
        SDL_GetWindowSize(get_ptr<SDL_Window>(), &result[0], &result[1]);
        return result;
    }

    int Window::get_width() const {
        return get_size()[0];
    }

    int Window::get_height() const {
        return get_size()[1];
    }

    WindowFlags Window::get_flags() const {
        return (WindowFlags)SDL_GetWindowFlags(get_ptr<SDL_Window>());
    }

    const char* Window::get_title() const {
        return SDL_GetWindowTitle(get_ptr<SDL_Window>());
    }

    void Window::set_bordered(bool bordered) {
        SDL_SetWindowBordered(get_ptr<SDL_Window>(), (bordered) ? SDL_TRUE : SDL_FALSE);
    }

    bool Window::set_brightness(float brightness) {
        return SDL_SetWindowBrightness(get_ptr<SDL_Window>(), brightness) == 0;
    }

    void* Window::set_data(const char* name, void* userData) {
        return SDL_SetWindowData(get_ptr<SDL_Window>(), name, userData);
    }
        uint32_t m_format;
        int m_width;
        int m_height;
        int m_refreshRate;
        void* m_driverData;

    bool Window::set_display_mode(const DisplayMode& mode) {
        SDL_DisplayMode sdldm = {
            mode.m_format,
            mode.m_width, mode.m_height,
            mode.m_refreshRate,
            mode.m_driverData,
        };
        return SDL_SetWindowDisplayMode(get_ptr<SDL_Window>(), &sdldm) == 0;
    }

    bool Window::set_fullscreen(WindowFlags flags) {
        return SDL_SetWindowFullscreen(get_ptr<SDL_Window>(), (uint32_t)flags) == 0;
    }

    bool Window::set_gamma_ramp(const GammaRamp& ramp) {
        return SDL_SetWindowGammaRamp(get_ptr<SDL_Window>(),
            &std::get<0>(ramp)[0],
            &std::get<1>(ramp)[0],
            &std::get<2>(ramp)[0]) == 0;
    }

    void Window::set_grab(bool grabbed) {
        SDL_SetWindowGrab(get_ptr<SDL_Window>(), (grabbed) ? SDL_TRUE : SDL_FALSE);
    }

    bool Window::set_hit_test(HitTestFunc callback, void* callbackData) {
        m_hitTestData.m_callback = callback;
        m_hitTestData.m_data = callbackData;
        if (callback != nullptr) {
            return SDL_SetWindowHitTest(get_ptr<SDL_Window>(),
                [](SDL_Window* window, const SDL_Point* area, void* data) -> SDL_HitTestResult {
                    auto hitTestData = reinterpret_cast<HitTestData*>(data);
                    return (SDL_HitTestResult)hitTestData->m_callback(Point(*area), hitTestData->m_data);
                },
                &m_hitTestData) == 0;
        }
        else {
            return SDL_SetWindowHitTest(get_ptr<SDL_Window>(), nullptr, nullptr) == 0;
        }
    }

    //void Window::d set_icon(const Surface& surface)

    bool Window::set_input_focus() {
        #if 1
        return true;
        #else
        return SDL_SetWindowInputFocus(get_ptr<SDL_Window>()) == 0;
        #endif
    }

    void Window::set_max_size(const Point& size) {
        SDL_SetWindowMaximumSize(get_ptr<SDL_Window>(), size[0], size[1]);
    }

    void Window::set_min_size(const Point& size) {
        SDL_SetWindowMinimumSize(get_ptr<SDL_Window>(), size[0], size[1]);
    }

    //void Window::d set_modal_for(Window& parent); FIXME: 2.0.5

    bool Window::set_opacity(float opacity) {
        #if 1
        return true;
        #else
        return SDL_SetWindowOpacity(get_ptr<SDL_Window>(), opacity);
        #endif
    }

    void Window::set_position(const Point& position) {
        SDL_SetWindowPosition(get_ptr<SDL_Window>(), position[0], position[1]);
    }

    void Window::set_resizable(bool resizable) {
        #if 1
        #else
        SDL_SetWindowResizable(get_ptr<SDL_Window>(), (resizable) ? SDL_TRUE : SDL_FALSE);
        #endif
    }

    void Window::set_size(const Point& size) {
        SDL_SetWindowSize(get_ptr<SDL_Window>(), size[0], size[1]);
    }

    void Window::set_title(const char* title) {
        SDL_SetWindowTitle(get_ptr<SDL_Window>(), title);
    }

    void Window::set_message_hook(MessageHook callback, void* userData) {
        internal::s_messageHookData.m_callback = callback;
        internal::s_messageHookData.m_data = userData;
        SDL_SetWindowsMessageHook([](void* userdata, void* hWnd, unsigned int message, uint64_t wParam, int64_t lParam) -> void {
                auto hookData = reinterpret_cast<internal::MessageHookData*>(userdata);
                hookData->m_callback(hookData->m_data, hWnd, message, wParam, lParam);
            },
            &internal::s_messageHookData);
    }
}