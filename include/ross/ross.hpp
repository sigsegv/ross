#pragma once

#include "types.hpp"
#include "color.hpp"
#include "vector2.hpp"
#include "line2.hpp"
#include "bbox.hpp"
#include "surface_rgb24.hpp"

namespace ross
{
    typedef color<3> color_rgb;
    typedef vector2<integer_t> vector2i;
    typedef vector2<real_t> vector2f;
    typedef vector2<size_t> vector2ui;
    typedef line2<real_t> line2f;
    using line2ui = line2<size_t>;
    using bboxui = bbox<size_t>;
    using bboxf = bbox<real_t>;
    
    template<typename T>
    inline vector2<T> floor(const vector2f& v)
    {
        return {(std::floor(v.x)), std::floor(v.y)};
    }

	template<>
	inline vector2ui floor(const vector2f& v)
	{
		return{ sizeT(std::floor(v.x)), sizeT(std::floor(v.y)) };
	}
    
    inline vector2i round(const vector2f& v)
    {
        return { std::llround(v.x), std::llround(v.y) };
    }
}

#include "canvas.hpp"



