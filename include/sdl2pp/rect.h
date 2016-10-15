#pragma once

#include <cstdint>
#include <tuple>
#include "assert.h"

struct SDL_Point;
struct SDL_Rect;

namespace sdl2 {
    class Rect;
    
    class Point {
    public:
        Point(int x, int y) : m_x(x), m_y(y) {}
        Point(const Point& other) : Point(other.m_x, other.m_y) {}
        Point(const std::tuple<int, int>& tuple)
            : Point(std::get<0>(tuple), std::get<1>(tuple)) {}
        Point() : Point(0, 0) {}
        Point(const SDL_Point& sdlPoint);

        Point& operator=(const Point& other) {
            m_x = other.m_x;
            m_y = other.m_y;
            return *this;
        }

        friend bool operator==(const Point& lhs, const Point& rhs);
        friend bool operator!=(const Point& lhs, const Point& rhs);
        friend class Rect;

        inline void as_sdl_point(SDL_Point& dest);
        
        // SDL function equivalents
        inline bool in_rect(const Rect& rect);

        // Accessors/Mutators
        inline std::tuple<int, int> get() const { return { m_x, m_y }; }
        inline int get_x() const { return m_x; }
        inline int get_y() const { return m_y; }

        inline void set(int x, int y) { m_x = x; m_y = y; }
        inline void set_x(int x) { m_x = x; }
        inline void set_y(int y) { m_y = y; }

    private:
        int m_x, m_y;
    };

    inline bool operator==(const Point& lhs, const Point& rhs) {
        return lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y;
    }

    inline bool operator!=(const Point& lhs, const Point& rhs) {
        return !(lhs == rhs);
    }

    class Rect {
    public:
        Rect(int x, int y, int width, int height)
            : m_position(x, y), m_width(width), m_height(height) {}
        Rect(const Point& position, int width, int height)
            : m_position(position), m_width(width), m_height(height) {}
        Rect(const Rect& other)
            : Rect(other.m_position, other.m_width, other.m_height) {}
        Rect()
            : m_position(0, 0), m_width(0), m_height(0) {}
        Rect(const SDL_Rect& sdlRect);

        Rect& operator=(const Rect& other) {
            m_position = other.m_position;
            m_width = other.m_width;
            m_height = other.m_height;
            return *this;
        }

        friend bool operator==(const Rect& lhs, const Rect& rhs);
        friend bool operator!=(const Rect& lhs, const Rect& rhs);

        inline void as_sdl_rect(SDL_Rect& dest);

        // SDL function equivalents
        inline bool is_empty() const;
        bool intersects(const Rect& other) const;
        Rect get_intersection(const Rect& other) const;
        Rect get_union(const Rect& other) const;
        Rect get_enclosure(const Point* points, int count, const Rect* clip) const;

        // static functions for creating special Rects
        // create a Rect that is the intersection of a and b
        inline static Rect create_intersection(const Rect& a, const Rect& b);
        // create a Rect that is the union of a and b
        inline static Rect create_union(const Rect& a, const Rect& b);
        // create a Rect that encloses all points
        inline static Rect create_enclosure(const Rect& r, const Point* points, int count, const Rect* clip);

        // Accessors/Mutators
        inline const Point& get_position() const { return m_position; }
        inline const int get_width() const { return m_width; }
        inline const int get_height() const { return m_height; }

        inline const int get_left() const { return m_position.m_x; }
        inline const int get_right() const { return m_position.m_x + m_width; }
        inline const int get_top() const { return m_position.m_y; }
        inline const int get_bottom() const { return m_position.m_y + m_height; }

        inline void set_position(const Point& position) { m_position = position; }
        inline void set_width(int width) { m_width = width; }
        inline void set_height(int height) { m_height = height; }

    private:
        Point m_position;
        int m_width, m_height;
    };

    inline bool operator==(const Rect& lhs, const Rect& rhs) {
        return lhs.m_position == rhs.m_position &&
            lhs.m_width == rhs.m_width &&
            lhs.m_height == rhs.m_height;
    }

    inline bool operator!=(const Rect& lhs, const Rect& rhs) {
        return !(lhs == rhs);
    }

    inline bool Rect::is_empty() const {
        return m_width <= 0 || m_height <= 0;
    }

    inline Rect Rect::create_intersection(const Rect& a, const Rect& b) {
        return a.get_intersection(b);
    }

    inline Rect Rect::create_union(const Rect& a, const Rect& b) {
        return a.get_union(b);
    }

    inline Rect Rect::create_enclosure(const Rect& r, const Point* points, int count, const Rect* clip) {
        return r.get_enclosure(points, count, clip);
    }
}