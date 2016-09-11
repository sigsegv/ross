#pragma once

#include "types.hpp"
#include "color.hpp"
#include "vector2.hpp"
#include "line2.hpp"
#include "surface_rgb24.hpp"

namespace ross
{
    typedef color<3> color_rgb;
    typedef vector2<integer_t> vector2i;
    typedef vector2<real_t> vector2f;
    typedef line2<real_t> line2f;
    
    template<typename T>
    constexpr vector2<T> floor(const vector2f& v)
    {
        return {std::floor(v.x), std::floor(v.y)};
    }
    
    inline const vector2i round(const vector2f& v)
    {
        return { std::llround(v.x), std::llround(v.y) };
    }
}

#include "canvas.hpp"



