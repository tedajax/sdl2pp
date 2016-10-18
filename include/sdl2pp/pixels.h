#pragma once

#include "stdinc.h"
#include <tuple>

namespace sdl2 {
    const uint8_t kAlphaOpaque = 255;
    const uint8_t kAlphaTransparent = 0;

    enum class PixelType : uint32_t {
        kUnknown,
        kIndex1,
        kIndex4,
        kIndex8,
        kPacked8,
        kPacked16,
        kPacked32,
        kArrayU8,
        kArrayU16,
        kArrayU32,
        kArrayF16,
        kArrayF32,
    };

    enum class Order : uint32_t {
        kBitmapNone = 0,
        kBitmap4321 = 1,
        kBitmap1234 = 2,

        kPackedNone = 0,
        kPackedXRGB = 1,
        kPackedRGBX = 2,
        kPackedARGB = 3,
        kPackedRGBA = 4,
        kPackedXBGR = 5,
        kPackedBGRX = 6,
        kPackedABGR = 7,
        kPackedBGRA = 8,

        kArrayNone = 0,
        kArrayRGB = 1,
        kArrayRGBA = 2,
        kArrayARGB = 3,
        kArrayBGR = 4,
        kArrayBGRA = 5,
        kArrayABGR = 6,
    };

    enum class Layout : uint32_t {
        kPackedNone,
        kPacked332,
        kPacked4444,
        kPacked1555,
        kPacked5551,
        kPacked565,
        kPacked8888,
        kPacked2101010,
        kPacked1010102,

        kNone = kPackedNone,
    };

    constexpr uint32_t get_pixel_format(PixelType type, Order order, Layout layout, uint32_t bits, uint32_t bytes) {
        return (1 << 28) | ((uint32_t)type << 24) | ((uint32_t)order << 20) |
            ((uint32_t)layout << 16) | (bits << 8) | (bytes << 0);
    }

    static FORCE_INLINE uint8_t get_format_flag(uint32_t format) {
        return (format >> 28) & 0x0F;
    }

    static FORCE_INLINE uint8_t get_format_type(uint32_t format) {
        return (format >> 24) & 0x0F;
    }

    static FORCE_INLINE uint8_t get_format_order(uint32_t format) {
        return (format >> 20) & 0x0F;
    }

    static FORCE_INLINE uint8_t get_format_layout(uint32_t format) {
        return (format >> 16) & 0x0F;
    }

    static FORCE_INLINE uint8_t get_format_bits(uint32_t format) {
        return (format >> 8) & 0xFF;
    }

    static FORCE_INLINE bool is_pixel_format_fourcc(uint32_t format) {
        return format && get_format_flag(format) != 1;
    }

    static FORCE_INLINE uint8_t get_format_bytes(uint32_t format) {
        if (is_pixel_format_fourcc(format)) {

        }
    }

    enum class PixelFormatTypes {
        kUnknown,
        kIndex1LSB = get_pixel_format(PixelType::kIndex1, Order::kBitmap4321, Layout::kNone, 1, 0),
        kIndex1MSB = get_pixel_format(PixelType::kIndex1, Order::kBitmap1234, Layout::kNone, 1, 0),
        kIndex4LSB = get_pixel_format(PixelType::kIndex4, Order::kBitmap4321, Layout::kNone, 4, 0),
        kIndex4MSB = get_pixel_format(PixelType::kIndex4, Order::kBitmap1234, Layout::kNone, 4, 0),
        kIndex8 = get_pixel_format(PixelType::kIndex8, Order::kPackedNone, Layout::kNone, 4, 0),
        kRGB332 = get_pixel_format(PixelType::kPacked8, Order::kPackedXRGB, Layout::kPacked332, 8, 1),
        kRGB444 = get_pixel_format(PixelType::kPacked16, Order::kPackedXRGB, Layout::kPacked4444, 12, 2),
        kRGB555 = get_pixel_format(PixelType::kPacked16, Order::kPackedXBGR, Layout::kPacked1555, 15, 2),
        kBGR555 = get_pixel_format(PixelType::kPacked16, Order::kPackedXRGB, Layout::kPacked1555, 15, 2),
        kARGB4444 = get_pixel_format(PixelType::kPacked16, Order::kPackedARGB, Layout::kPacked4444, 16, 2),
        kRGBA4444 = get_pixel_format(PixelType::kPacked16, Order::kPackedRGBA, Layout::kPacked4444, 16, 2),
        kABGR4444 = get_pixel_format(PixelType::kPacked16, Order::kPackedABGR, Layout::kPacked4444, 16, 2),
        kBGRA4444 = get_pixel_format(PixelType::kPacked16, Order::kPackedBGRA, Layout::kPacked4444, 16, 2),
        kARGB1555 = get_pixel_format(PixelType::kPacked16, Order::kPackedARGB, Layout::kPacked1555, 16, 2),
        kRGBA5551 = get_pixel_format(PixelType::kPacked16, Order::kPackedRGBA, Layout::kPacked5551, 16, 2),
        kABGR1555 = get_pixel_format(PixelType::kPacked16, Order::kPackedABGR, Layout::kPacked1555, 16, 2),
        kBGRA5551 = get_pixel_format(PixelType::kPacked16, Order::kPackedBGRA, Layout::kPacked5551, 16, 2),
        kRGB565 = get_pixel_format(PixelType::kPacked16, Order::kPackedXRGB, Layout::kPacked565, 16, 2),
        kBGR565 = get_pixel_format(PixelType::kPacked16, Order::kPackedXBGR, Layout::kPacked565, 16, 2),
        kRGB24 = get_pixel_format(PixelType::kArrayU8, Order::kArrayRGB, Layout::kNone, 24, 3),
        kBGR24 = get_pixel_format(PixelType::kArrayU8, Order::kArrayBGR, Layout::kNone, 24, 3),
        kRGB888 = get_pixel_format(PixelType::kPacked32, Order::kPackedXRGB, Layout::kPacked8888, 24, 4),
        kRGBX8888 = get_pixel_format(PixelType::kPacked32, Order::kPackedRGBX, Layout::kPacked8888, 24, 4),
        kBGR888 = get_pixel_format(PixelType::kPacked32, Order::kPackedXBGR, Layout::kPacked8888, 24, 4),
        kBGRX8888 = get_pixel_format(PixelType::kPacked32, Order::kPackedBGRX, Layout::kPacked8888, 24, 4),
        kARGB8888 = get_pixel_format(PixelType::kPacked32, Order::kPackedARGB, Layout::kPacked8888, 32, 4),
        kRGBA8888 = get_pixel_format(PixelType::kPacked32, Order::kPackedRGBA, Layout::kPacked8888, 32, 4),
        kABGR8888 = get_pixel_format(PixelType::kPacked32, Order::kPackedABGR, Layout::kPacked8888, 32, 4),
        kBGRA8888 = get_pixel_format(PixelType::kPacked32, Order::kPackedBGRA, Layout::kPacked8888, 32, 4),
        kARGB2101010 = get_pixel_format(PixelType::kPacked32, Order::kPackedARGB, Layout::kPacked2101010, 32, 4),
        kYV12 = fourcc('Y', 'V', '1', '2'),
        kIYUV = fourcc('I', 'Y', 'U', 'V'),
        kYUY2 = fourcc('Y', 'U', 'Y', '2'),
        kUYVY = fourcc('U', 'Y', 'V', 'Y'),
        kYVYU = fourcc('Y', 'V', 'Y', 'U'),
        kNV12 = fourcc('N', 'V', '1', '2'),
        kNV21 = fourcc('N', 'V', '2', '1'),
    };

    FORCE_INLINE uint8_t col_ftob(float v) {
        return (uint8_t)(clamp01(v) * 255.f);
    }

    FORCE_INLINE float col_btof(uint8_t v) {
        return (float)v / 255.f;
    }

    class Color {
    public:
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
            : m_r(r), m_g(g), m_b(b), m_a(a) {}
        Color(int r, int g, int b, int a = 255)
            : Color((uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)a) {}
        Color() : Color(0, 0, 0, 255) {}
        Color(float r, float g, float b, float a = 1.f)
            : Color(col_ftob(r), col_ftob(g), col_ftob(b), col_ftob(a)) {}

        inline std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> get() const { return { m_r, m_g, m_b, m_a }; }
        inline std::tuple<float, float, float, float> get_floats() const { return { col_btof(m_r), col_btof(m_g), col_btof(m_b), col_btof(m_a) }; }

        inline uint8_t& operator[](int index) { return ((uint8_t*)this)[index]; }
        inline const uint8_t& operator[](int index) const { return ((uint8_t*)this)[index]; }

        inline uint8_t get_r() const { return m_r; }
        inline uint8_t get_g() const { return m_g; }
        inline uint8_t get_b() const { return m_b; }
        inline uint8_t get_a() const { return m_a; }

        inline void set_r(uint8_t r) { m_r = r; }
        inline void set_g(uint8_t g) { m_g = g; }
        inline void set_b(uint8_t b) { m_b = b; }
        inline void set_a(uint8_t a) { m_a = a; }

        static const Color kWhite, kBlack, kGrey, kClear, kRed, kGreen, kBlue,
            kCyan, kMagenta, kYellow;

        friend bool operator==(const Color&, const Color&);
        friend bool operator!=(const Color&, const Color&);

        Color get_union(const Color& other) const;
        Color get_intersection(const Color& other) const;

    private:
        uint8_t m_r, m_g, m_b, m_a;
    };

    inline bool operator==(const Color& lhs, const Color& rhs) {
        return lhs.m_r == rhs.m_r &&
            lhs.m_g == rhs.m_g &&
            lhs.m_b == rhs.m_b &&
            lhs.m_a == rhs.m_a;
    }

    inline bool operator!=(const Color& lhs, const Color& rhs) {
        return lhs.m_r != rhs.m_r ||
            lhs.m_g != rhs.m_g ||
            lhs.m_b != rhs.m_b ||
            lhs.m_a != rhs.m_a;
    }

    inline Color operator+(const Color& lhs, const Color& rhs) {
        return Color(clamp(lhs.m_r + rhs.m_r, 0, 255),
            clamp(lhs.m_g + rhs.m_g, 0, 255),
            clamp(lhs.m_b + rhs.m_b, 0, 255),
            clamp(lhs.m_a + rhs.m_a, 0, 255));
    }

    inline Color operator-(const Color& lhs, const Color& rhs) {
        return Color(clamp(lhs.m_r - rhs.m_r, 0, 255),
            clamp(lhs.m_g - rhs.m_g, 0, 255),
            clamp(lhs.m_b - rhs.m_b, 0, 255),
            clamp(lhs.m_a - rhs.m_a, 0, 255));
    }

    inline Color operator*(const Color& lhs, const Color& rhs) {
        float r1, g1, b1, a1;
        float r2, g2, b2, a2;
        std::tie(r1, g1, b1, a1) = lhs.get_floats();
        std::tie(r2, g2, b2, a2) = rhs.get_floats();
        return Color(r1 * r2, g1 * g2, b1 * b2, a1 * a2);
    }

    inline Color operator*(const Color& lhs, float rhs) {
        float r, g, b, a;
        std::tie(r, g, b, a) = lhs.get_floats();
        return Color(r * rhs, g * rhs, b * rhs, a);
    }
}