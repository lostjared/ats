#ifndef TEE_STREAMBUF_HPP
#define TEE_STREAMBUF_HPP

#include <iostream>
#include <streambuf>
#include <sstream> 
#include<memory>


namespace interp {

    class tee_streambuf : public std::streambuf {
    public:
        tee_streambuf(std::streambuf* sb1, std::streambuf* sb2);

    private:
        std::streambuf* sb1_;
        std::streambuf* sb2_;

    protected:
        virtual int_type overflow(int_type c = traits_type::eof()) override;
        virtual int sync() override;
    };
    void setup_tee_for_interp_stream();

} 

#endif