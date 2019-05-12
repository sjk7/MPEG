#include "../DJMPEGlib/include/DJMPEGlib.hpp"
#include <string_view>
#include <iostream>
#include <fstream>
#include <cassert>
#include <exception>

using namespace std;
using namespace dj::MPEG;

dj::MPEG::error read_mp3(std::string_view filepath) {

    LOGIT("Program started");
    LOGIT("sizeof(size_t) = ", sizeof(size_t));

    std::fstream f(filepath.data(), std::ios::in | std::ios::binary);
    assert(f);
    char buffer[8192] = {0};

    mpeg m(filepath,
        [&](auto& bv,
            my::io::byte_count_type reqcb = my::io::byte_count_type::default_value,
            my::seek_type&& sk = my::seek_type()) {
            if (bv.empty()) {
                bv = my::buf_view<char>(buffer);
            }
            const std::streamsize wanted
                = my::types::to_int(reqcb) < 0 ? 8192 : my::types::to_int(reqcb);

            int ret = NO_ERROR;

            if (sk.dir != my::seek_type::seek_direction::none) {
                f.clear();
                f.seekg(my::types::cast(sk.how_much, std::streamoff()),
                    static_cast<ios_base::seekdir>(sk.dir));
                if (!f) {
                    LOGERR("file ", filepath, "was asked to seek to ", sk.how_much, ":",
                        my::seek_type::seek_direction_string(sk), "but failed");
                    assert(0);
                }
            }

            try {
                f.clear();
                auto d = bv.data();
                f.read(d, wanted);
                const auto read = f.gcount();
                assert(read > 0);

                bv.set_size(static_cast<int>(read));
                if (f.eof()) {
                    ret = END_OF_FILE;
                }

            } catch (const std::exception& e) {
                LOGERR("error reading file:\n", filepath, e.what());
            }

            return 0;
        });
    return dj::MPEG::error::none;
}

int main() {

#ifdef _WIN32
    std::string path("C:\\test.mp3");
#else
    std::string path("/home/hp/Documents/code/MPEG/ztest_files/128.mp3");
#endif
    read_mp3(path);
    return 0;
}
