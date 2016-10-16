#include <SDL2/SDL.h>

#include <algorithm>
#include <functional>

#include "rect.h"

namespace sdl2 {
    Point::Point(const SDL_Point& sdlPoint)
        : m_x(sdlPoint.x), m_y(sdlPoint.y) {}

    inline void Point::as_sdl_point(SDL_Point& dest) const {
        dest.x = m_x;
        dest.y = m_y;
    }

    inline bool Point::in_rect(const Rect& rect) const {
        if (rect.is_empty()) {
            return false;
        }
        return m_x >= rect.get_left() &&
            m_x <= rect.get_right() &&
            m_y >= rect.get_top() &&
            m_y <= rect.get_bottom();
    }

    Rect::Rect(const SDL_Rect& sdlRect)
        : Rect(sdlRect.x, sdlRect.y, sdlRect.w, sdlRect.h) {}

    inline void Rect::as_sdl_rect(SDL_Rect& dest) {
        dest.x = m_position.get_x();
        dest.y = m_position.get_y();
        dest.w = m_width;
        dest.h = m_height;
    }

    bool Rect::contains_point(const Point& point) const {
        return point.in_rect(*this);
    }

    void Rect::enclose(const Point& point) {
        if (is_empty()) {
            m_position = point;
            m_width = 0;
            m_height = 0;
            return;
        }

        int left = std::min(get_left(), point.get_x());
        int right = std::max(get_right(), point.get_x());
        int top = std::min(get_top(), point.get_y());
        int bottom = std::max(get_bottom(), point.get_y());
        m_position.set(left, top);
        m_width = right - left;
        m_height = bottom - top;
    }

    bool Rect::intersects(const Rect& other) const {
        if (is_empty() || other.is_empty()) {
            return false;
        }

        return get_right() >= other.get_left() &&
            get_left() <= other.get_right() &&
            get_bottom() >= other.get_top() &&
            get_top() <= other.get_bottom();
    }

    Rect Rect::get_intersection(const Rect& other) const {
        Rect result;

        if (is_empty() || other.is_empty()) {
            result.m_width = 0;
            result.m_height = 0;
            return result;
        }

        int left = std::max(get_left(), other.get_left());
        int top = std::max(get_top(), other.get_top());

        int right = std::min(get_right(), other.get_right());
        int bottom = std::min(get_bottom(), other.get_bottom());

        result.set_position(Point(left, top));
        result.set_width(right - left);
        result.set_height(bottom - top);

        return result;
    }

    Rect Rect::get_union(const Rect& other) const {
        // Special cases for empty rects
        if (is_empty()) {
            if (other.is_empty()) {
                return Rect();
            }
            else {
                return other;
            }
        }
        else {
            if (other.is_empty()) {
                return *this;
            }
        }

        Rect result;

        int left = std::min(get_left(), other.get_left());
        int top = std::min(get_top(), other.get_top());

        int right = std::max(get_right(), other.get_right());
        int bottom = std::max(get_bottom(), other.get_bottom());

        result.set_position(Point(left, top));
        result.set_width(right - left);
        result.set_height(bottom - top);

        return result;
    }

    Rect Rect::get_enclosure(const Point* points, int count) const {
        Rect result = *this;

        for (int i = 0; i < count; ++i) {
            result.enclose(points[i]);
        }

        return result;
    }

    Rect Rect::get_enclosure(const Point* points, int count, const Rect& clip, int* const outEnclosedCount /* = nullptr */) const {
        Rect result = *this;

        int clipCount = 0;
        for (int i = 0; i < count; ++i) {
            if (clip.contains_point(points[i])) {
                result.enclose(points[i]);
                ++clipCount;
            }
        }

        if (outEnclosedCount) {
            *outEnclosedCount = clipCount;
        }

        return result;
    }
}