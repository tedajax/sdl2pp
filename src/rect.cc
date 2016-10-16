#include <SDL2/SDL.h>

#include <algorithm>
#include <functional>

#include "rect.h"

namespace sdl2 {
    Point::Point(const SDL_Point& sdlPoint) 
        : m_x(sdlPoint.x), m_y(sdlPoint.y) {}

    inline void Point::as_sdl_point(SDL_Point& dest) {
        dest.x = m_x;
        dest.y = m_y;
    }

    inline bool Point::in_rect(const Rect& rect) {
        return m_x >= rect.get_left() &&
            m_x <= rect.get_right() &&
            m_y >= rect.get_top() &&
            m_y <= rect.get_bottom();
    }

    Rect::Rect(const SDL_Rect& sdlRect)
        : Rect(sdlRect.x, sdlRect.y, sdlRect.w, sdlRect.h) {}

    inline int rect_get_left(const Rect& r) { return r.get_left(); }
    inline int rect_get_right(const Rect& r) { return r.get_right(); }
    inline int rect_get_top(const Rect& r) { return r.get_top(); }
    inline int rect_get_bottom(const Rect& r) { return r.get_bottom(); }

    inline std::tuple<int, int> get_min_and_max(const Rect& a, const Rect& b, std::function<int(const Rect&)> getMinFunc, std::function<int(const Rect&)> getMaxFunc) {
        int Amin = std::max(getMinFunc(a), getMinFunc(b));
        int Amax = std::min(getMaxFunc(a), getMaxFunc(b));
        return { Amin, Amax };
    }

    inline void Rect::as_sdl_rect(SDL_Rect& dest) {
        dest.x = m_position.get_x();
        dest.y = m_position.get_y();
        dest.w = m_width;
        dest.h = m_height;
    }

    bool Rect::intersects(const Rect& other) const {
        if (is_empty() || other.is_empty()) {
            return false;
        }

        int minV, maxV;

        std::tie(minV, maxV) = get_min_and_max(*this, other, rect_get_left, rect_get_right);
        if (maxV <= minV) {
            return false;
        }

        std::tie(minV, maxV) = get_min_and_max(*this, other, rect_get_top, rect_get_bottom);
        if (maxV <= minV) {
            return false;
        }

        return true;
    }

    Rect Rect::get_intersection(const Rect& other) const {
        Rect result;

        if (is_empty() || other.is_empty()) {
            result.m_width = 0;
            result.m_height = 0;
            return result;
        }

        int minV, maxV;

        std::tie(minV, maxV) = get_min_and_max(*this, other, rect_get_left, rect_get_right);
        result.m_position.set_x(minV);
        result.set_width(maxV - minV);

        std::tie(minV, maxV) = get_min_and_max(*this, other, rect_get_top, rect_get_bottom);
        result.m_position.set_y(minV);
        result.set_height(maxV - minV);

        return result;
    }

    Rect Rect::get_union(const Rect& other) const {
        return *this;
    }

    Rect Rect::get_enclosure(const Point* points, int count, const Rect* clip) const {
        return *this;
    }
}