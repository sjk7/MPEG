#pragma once

#include "my_logging.hpp"
#include "my_types.hpp"
#include <cstring>
#include <cstdio>
#include <cstddef>

namespace my {
namespace io {
    enum class byte_count_type : int { default_value = -1 };
    enum class byte_offset_type : int { default_value = -1 };
    enum class large_size_type : int64_t { default_value = -1 };
    enum class large_offset_type : int64_t { default_value = -1 };
} // namespace io

struct seek_type {
    enum seek_direction : int8_t {
        none = -1,
        cur = std::ios_base::cur,
        beg = std::ios_base::beg,
        end = std::ios_base::end
    };

    static std::string seek_direction_string(const seek_type sd) {
        switch (sd.dir) {
            case seek_direction::cur: return "from_current";
            case seek_direction::end: return "from_end";
            default: return "none";
        };
    }
    my::io::large_offset_type how_much = {my::io::large_offset_type::default_value};
    seek_direction dir = {seek_direction::none};

    seek_type(const my::io::large_offset_type where_to,
        const seek_direction dir = seek_direction::none)
        : how_much(where_to), dir(dir) {}
    seek_type() = default;
};

template <typename T> struct buf_view {

    private:
    static constexpr size_t ele_size = sizeof(T);
    T* m_beg{nullptr};
    T* m_end{nullptr};

    public:
    buf_view() noexcept = default;
    constexpr buf_view(T* beg, T* end) noexcept : m_beg(beg), m_end(end) {}
    constexpr buf_view(T* beg, size_t sz) noexcept : m_beg(beg), m_end(m_beg + sz) {}
    template <typename X, size_t size>
    constexpr buf_view(X (&b)[size]) noexcept : m_beg(b), m_end(m_beg + size) {}
    constexpr buf_view(const buf_view& rhs) noexcept = default;
    constexpr buf_view& operator=(const buf_view& rhs) noexcept = default;
    constexpr buf_view& operator=(buf_view&& rhs) noexcept = default;

    constexpr bool empty() const noexcept {
        return m_beg == m_end || m_beg == nullptr || m_end == nullptr;
    }

    constexpr const T* begin() noexcept { return m_beg; }
    constexpr const T* end() noexcept { return m_end; }
    constexpr size_t size() const noexcept { return m_end - m_beg; }
    constexpr int size_i() const noexcept { return static_cast<int>(size()); }
    constexpr ptrdiff_t size_pdiff() const noexcept {
        return static_cast<ptrdiff_t>(size());
    }

    constexpr auto data() { return m_beg; }
    constexpr void set_size(int new_size) noexcept { m_end = m_beg + new_size; }

}; // namespace my
} // namespace my
