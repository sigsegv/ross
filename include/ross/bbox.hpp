#pragma once

#include <cstdlib>
#include <algorithm>

namespace ross
{
/**
 * Immutable POD 2D axis aligned bounding box
 */
template<typename T>
class bbox
{
public:
    /**
     * Create BBox from two points
     */
    bbox(const vector2<T>& p1, const vector2<T>& p2) :
        _top_left({std::min(p1.x, p2.x), std::min(p1.y, p2.y)}),
        _width(p1.x > p2.x ? p1.x - p2.x : p2.x - p1.x),
        _height(p1.y > p2.y ? p1.y - p2.y : p2.y - p1.y)
    {
        
    }
    
    static bbox empty() noexcept
    {
        return bbox({0,0},{0,0});
    }
    
    constexpr T width() const noexcept
    {
        return _width;
    }
    
    constexpr T height() const noexcept
    {
        return _height;
    }
    
    constexpr T left() const noexcept
    {
        return _top_left.x;
    }
    
    constexpr T top() const noexcept
    {
        return _top_left.y;
    }
    
    constexpr T right() const noexcept
    {
        return _top_left.x + _width;
    }
    
    constexpr T bottom() const noexcept
    {
        return _top_left.y + _height;
    }
    
    constexpr line2<T> left_edge() const noexcept
    {
        return line2<T>{_top_left, {top(), right()}};
    }
    
    constexpr line2<T> top_edge() const noexcept
    {
        return line2<T>{_top_left, {right(), top()}};
    }
    
    constexpr line2<T> right_edge() const noexcept
    {
        return line2<T>{{right(), top()}, {right(), bottom()}};
    }
    
    constexpr line2<T> bottom_edge() const noexcept
    {
        return line2<T>{{left(), bottom()}, {right(), bottom()}};
    }
    
    constexpr T area() const noexcept
    {
        return _width * _height;
    }
    
    /**
     * Union of this and other
     *
     * @param other bbox to union
     * @returns union of this and other
     */
    bbox merge(const bbox& other) const noexcept
    {
        const T l = std::min(left(), other.left());
        const T t = std::min(top(), other.top());
        const T r = std::max(right(), other.right());
        const T b = std::max(bottom(), other.bottom());
        return bbox({l, t}, {r, b});
    }
    
    /**
     * Intersection of this and other
     *
     * @param other bbox
     * @returns intersection of this and other
     */
    bbox intersect(const bbox& other) const noexcept
    {
        if(other.left() > right() || left() > other.right()) return empty();
        if(other.bottom() < top() || other.top() > bottom()) return empty();
        
        const T l = std::max(left(), other.left());
        const T t = std::max(top(), other.top());
        const T r = std::min(right(), other.right());
        const T b = std::min(bottom(), other.bottom());
        return bbox({l, t}, {r, b});
    }
    
    constexpr bool contains(const vector2<T>& point) const noexcept
    {
        return left() < point.x && right() > point.x && top() < point.y && bottom() > point.y;
    }
    
    /**
     * Checks if any part of line is inside this
     *
     * @param line to check
     * @returns true if any part of line inside this
     */
//    constexpr bool contains(const line2<T>& line) const noexcept
//    {
//        bbox<T> b{line.u, line.v};
//        if(intersect(b).is_empty()) return false;
//        
//        
//    }
    
    /**
     * check if bbox is an empty one
     *
     * @returns true if empty BBox, otherwise false
     */
    constexpr bool is_empty() const noexcept
    {
        return _width == 0 && _height == 0;
    }

private:
    const vector2<T> _top_left;
    const T _width, _height;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const bbox<T>& b)
{
    return os << "<" << b.left() << ", " << b.top() << ", " << b.right() << ", " << b.bottom() << ">";
}
    
}