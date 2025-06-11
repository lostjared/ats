#include "tee_streambuf.hpp"
#include "code.hpp" 
#include <iostream>
#include <memory>

namespace interp {

    tee_streambuf::tee_streambuf(std::streambuf* sb1, std::streambuf* sb2)
        : sb1_(sb1), sb2_(sb2) {
        if (!sb1_ || !sb2_) {
            throw std::invalid_argument("Stream buffers cannot be null");
        }
    }

    std::streambuf::int_type tee_streambuf::overflow(int_type c) {
        if (traits_type::eq_int_type(c, traits_type::eof())) {
            return sync() == 0 ? traits_type::not_eof(c) : traits_type::eof();
        }
        bool eof1 = traits_type::eq_int_type(sb1_->sputc(c), traits_type::eof());
        bool eof2 = traits_type::eq_int_type(sb2_->sputc(c), traits_type::eof());
        if (eof1 || eof2) {
            return traits_type::eof();
        }
        return c;
    }

    int tee_streambuf::sync() {
        bool err1 = (sb1_->pubsync() == -1);
        bool err2 = (sb2_->pubsync() == -1);
        if (err1 || err2) {
            return -1; 
        }
        return 0; 
    }


    static std::unique_ptr<tee_streambuf> global_tee_sbuf = nullptr;
    static std::streambuf* original_interp_sbuf = nullptr;

    void setup_tee_for_interp_stream() {
        if (!global_tee_sbuf) {
            original_interp_sbuf = interp::stream.rdbuf();
            global_tee_sbuf = std::make_unique<tee_streambuf>(original_interp_sbuf, std::cout.rdbuf());
            static_cast<std::ostream&>(interp::stream).rdbuf(global_tee_sbuf.get());
        }
    }

    void cleanup_tee_for_interp_stream() {
        if (global_tee_sbuf && original_interp_sbuf) {
            static_cast<std::ostream&>(interp::stream).rdbuf(original_interp_sbuf);
            global_tee_sbuf.reset();
            original_interp_sbuf = nullptr;
        }
    }

}