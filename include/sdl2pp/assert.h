#pragma once

#if defined(_MSC_VER)
#   define BREAKPOINT() __debugbreak()
#else
#   define BREAKPOINT() __asm__("int $3")
#endif

#define ASSERT_ALWAYS(exp, ...) do { \
        static bool _skipAssert = false; \
        if (!_skipAssert && !(exp)) { \
            printf("\n---------------\nASSERT(%s) %s:%d -- %s\n---------------\n", #exp, __FILE__, __LINE__, ##__VA_ARGS__); \
            BREAKPOINT(); \
        } \
    } while (0);

#ifdef DEBUG
#   define ASSERT ASSERT_ALWAYS
#else
#   define ASSERT(exp, ...) ((void)0)
#endif