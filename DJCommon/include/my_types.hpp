#pragma once
// my_types.hpp
#include <utility>
#include <cstddef>
#include <iosfwd>

namespace my {
namespace types {

    // You may well need "using namespace my::types" to
    // be able to use these conversion functions.

    // SFINAE-friendly way to get underlying type of some strong enum.
    template <class T, bool = std::is_enum<T>::value>
    struct get_underlying_type : std::underlying_type<T> {
        using type = std::underlying_type_t<T>;
    };

    template <class T>
    struct get_underlying_type<T,
        false /* is_enum */> { /* type underlying_type does not exist */
    };

    template <typename E> using UT = typename get_underlying_type<E>::type;

    template <typename FROM, typename TO>
    inline constexpr TO cast(FROM&& from, const TO&&) noexcept {
        return static_cast<TO>(std::forward<FROM&&>(from));
    }

    template <typename FROM, typename TO>
    inline constexpr TO cast(const FROM& from, const TO&&) noexcept {
        return static_cast<TO>(from);
    }

    template <typename T> inline constexpr int to_int(T&& t) noexcept {
        return cast(std::forward<T&&>(t), std::forward<int&&>(int{0}));
    }

    template <typename FROM, typename U = UT<FROM>>
    inline constexpr typename std::underlying_type<FROM>::type cast(FROM e) noexcept {
        return static_cast<typename std::underlying_type<FROM>::type>(e);
    }

    template <typename T> constexpr inline size_t to_size_t(const T& t) noexcept {
        return cast(t, size_t{});
    }

    template <typename E, typename U = UT<E>>
    constexpr inline std::ostream& operator<<(std::ostream& os, const E& e) noexcept {

        using UT = typename std::underlying_type_t<E>;
        auto val = cast(e, UT{});
        os << val;
        return os;
    }

} // namespace types
} // namespace my
