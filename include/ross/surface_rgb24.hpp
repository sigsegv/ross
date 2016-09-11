#pragma once

#include <cstdint>
#include <ross/ross.hpp>

namespace ross
{
template<integer_t W, integer_t H>
class surface_rgb24
{
public:
    surface_rgb24()
    {
        data = new std::uint8_t[W * H * 3];
    }
    
    integer_t width() const
    {
        return W;
    }
    
    integer_t height() const
    {
        return H;
    }
    
    ~surface_rgb24()
    {
        delete data;
    }
    
    
    std::uint8_t* data;
};
}