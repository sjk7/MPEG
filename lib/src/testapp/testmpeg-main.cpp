#include "../DJMPEGlib/include/DJMPEGlib.hpp"
#include <string_view>
#include <iostream>
#include <fstream>
#include <cassert>
#include <exception>

using namespace std;
using namespace dj::MPEG;

int read_mp3(std::string_view filepath) {

    LOGIT("Program started");
    std::fstream f(filepath.data(), std::ios::in | std::ios::binary);
    assert(f);
    char buffer[8192];

    mpeg m(filepath,
        [&](auto& bv, int reqcb = -1, my::seek_type&& sk = my::seek_type()) {
            if (bv.empty()) {
                bv = my::buf_view<char>(buffer);
            }
            const std::streamsize wanted = reqcb < 0 ? 8192 : reqcb;

            if (reqcb < 0) { reqcb = 8192;
}
            assert(reqcb > 0 && reqcb <= 8192);
            int ret = NO_ERROR;

            if (sk.dir != my::seek_type::seek_direction::none) {
                f.clear();
                f.seekg(sk.how_much, sk.dir);
                if (!f) {
                    LOGERR("file ", filepath, "was asked to seek to ",
                        sk.how_much, ":",
                        my::seek_type::seek_direction_string(sk), "but failed");
                    assert(0);
                }
            }

            try {
                f.clear();
                auto d = bv.data();
                f.read(d, reqcb);
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
    return 0;
}

int main() {
    read_mp3("C:\\test.mp3");
    return 0;
}
