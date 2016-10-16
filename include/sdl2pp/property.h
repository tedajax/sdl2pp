#pragma once

#include <functional>
#include <initializer_list>

// Property<int, &m_value, [](int* self) { return *self; }, [](int* self, const auto& value) { *self = value; }> m_property;

template<typename T, T* PTR, const T&(*GET)(T*) = nullptr, void(*SET)(T*, const T&) = nullptr>
class Property {
    void operator=(const T& value) {
        if (SET) {
            SET(PTR, value);
        }
        else {
            *PTR = value;
        }
    }

    operator T() const {
        if (GET) {
            return GET(PTR);
        }
        return *PTR;
    }
};
