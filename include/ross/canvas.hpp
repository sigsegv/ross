#pragma once

#include <cstdint>
#include <cmath>
#include <array>
#include <ross/ross.hpp>
#include <ross/detail/algorithms.hpp>

namespace ross
{
class canvas
{
public:
    /**
     * Create a drawing canvas.
     *
     * @param dimension the width and height of the final raster
     */
    canvas(const vector2ui& dimension) :
        dimension(dimension),
        m_data(new uint8_t[dimension.x * dimension.y * 3])
    {
        
    }
    
    ~canvas()
    {
        delete[] m_data;
    }
    
    /**
     * returns pointer to raw RGB24 data
     */
    uint8_t* data()
    {
        return m_data;
    }
    const uint8_t* data() const
    {
        return m_data;
    }
    
    size_t size() const
    {
        return dimension.x * dimension.y * 3;
    }
    /**
     * Draw line from p1 to p2 using color
     */
    void draw_line(const vector2f& p1, const vector2f& p2, const color_rgb& color)
    {
        scan_line(p1, p2, color);
    }
    
    void set_pixel(const vector2ui& point, const color_rgb& color)
    {
        size_t offset = ((point.y * dimension.x) + point.x) * 3;
        m_data[offset    ] = static_cast<uint8_t>(color[0] * 0xFF);
        m_data[offset + 1] = static_cast<uint8_t>(color[1] * 0xFF);
        m_data[offset + 2] = static_cast<uint8_t>(color[2] * 0xFF);
    }
    
    const vector2ui dimension;
private:
    uint8_t* m_data;
    
    void scan_line(const vector2f& p1, const vector2f& p2, const color_rgb& color)
    {/*
        const vector2f delta = (p2 - p1).normalized();
        const bool x_dominant = std::abs(delta.x) > std::abs(delta.y);
        vector2f device_v = p1;
        while(true)
        {
            
            if(x_dominant)
            {
                
            }
            else
            {
                
            }
        }*/
    }
    
    /* Bresenham’s algorithm (1965)
    // Graphic Gems 1 II.8
    integer_t sgn(integer_t x)
    {
        return x > 0.0 ? 1.0 : -1.0;
    }
    
    void digline(const vector2i& p1, const vector2i& p2, const color_rgb& color)
    {
        integer_t d, x, y, ax, ay, sx, sy, dx, dy;
        dx = p2.x - p1.x;
        dy = p2.y - p1.y;
        ax = std::abs(dx)*2;
        ay = std::abs(dy)*2;
        sx = sgn(dx);
        sy = sgn(dy);
        x = p1.x;
        y = p1.y;
        if(ax > ay) // x dominant
        {
            d = ay - ax / 2;
            set_pixel({x,y}, color);
        }
        
    }*/
};
}