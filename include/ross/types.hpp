#pragma once

#if defined _DEBUG
#include <cassert>
#include <limits>
#endif

namespace ross
{
    typedef double real_t;
    typedef int64_t integer_t;
    typedef size_t size_t;
    
    constexpr real_t kPI   = 3.14159265358979323846;
    constexpr real_t kPI_4 = 0.785398163397448309616;

	template<typename T>
	inline size_t sizeT(T v)
	{
		return static_cast<size_t>(v);
	}

#if defined _DEBUG 
	inline size_t sizeT(real_t v)
	{
		assert(v > 0.0);
		assert(v < static_cast<real_t>(std::numeric_limits<size_t>::max()));
		return static_cast<size_t>(v);
	}
#endif
}