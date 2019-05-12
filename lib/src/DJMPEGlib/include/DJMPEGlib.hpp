#pragma once
#include "../../../../DJCommon/include/my_buf_view.hpp"
#include <string_view>
#include <string>
#include <cassert>
#include <cstdio>

namespace dj {

namespace MPEG {
    enum class error : uint16_t { none = 0, kind_flag = 0 };

    inline error error_default() { return error::none; }

    template <typename IO> class mpeg {

        private:
        char m_internal_buf[2048] = {0};
        std::string m_spath;
        IO& m_io;
        struct dummy_type {};
        my::buf_view<char> m_buf;

        mpeg(std::string_view&& sv, IO&& io, dummy_type dt) noexcept
            : m_spath(sv), m_io(io) {
            (void)dt;
        }

        int io_read(IO&& io,
            my::io::byte_count_type cbwanted = my::io::byte_count_type::default_value,
            my::seek_type sk = my::seek_type()) noexcept {
            int read = io(m_buf, cbwanted, std::forward<my::seek_type&&>(sk));
            LOGERR("This is some error");

            return read;
        }

        public:
        mpeg(std::string_view sv, IO&& io)
            : mpeg(std::forward<std::string_view>(sv), std::forward<IO&&>(io),
                  dummy_type{}) {

            io_read(std::forward<IO&&>(m_io), my::io::byte_count_type::default_value);
        }
    }; // namespace MPEG
} // namespace MPEG
} // namespace dj
