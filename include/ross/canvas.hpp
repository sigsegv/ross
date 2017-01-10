#pragma once

#include <cstdint>
#include <cmath>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <algorithm>
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
		//midpoint_line(p1, p2, color);
        symwuline(p1, p2, color);
    }

	/**
	* Draw line from p1 to p2 using color
	*/
	void draw_line(const vector2f& p1, const vector2f& p2, real_t width, const color_rgb& color)
	{
		//midpoint_line(p1, p2, color);
		//symwuline(p1, p2, color);
		//scan_line(p1, p2, width, color);
	}

	struct edge_t
	{
		real_t y_max, x_min, slope_inv, x;
	};

	struct edge_sort
	{
		bool operator()(const edge_t& a, const edge_t& b) { return a.x_min < b.x_min; }
	};

	using edge_bucket_t = std::vector<edge_t>;
	using edge_table_t = std::map<real_t, edge_bucket_t>;
	using active_edge_table_t = std::list<edge_t>;

	void stroke_path(std::vector<vector2f>& path, const color_rgb& stroke_color, real_t width)
	{
		// Build edges

	}

	void fill_path(std::vector<vector2f>& path, const color_rgb& color)
	{
		using edge_bucket_t = std::vector<edge_t>;
		using edge_table_t = std::map<real_t, edge_bucket_t>;

		if (path.size() < 2) return;

		edge_table_t edge_table;

		// Build edges
		std::vector<vector2f>::const_iterator curr, next, end = path.end();
		for (curr = path.begin(), next = curr + 1; next != end; ++curr, ++next)
		{
			edge_t edge;
			edge.y_max = std::max(curr->y, next->y);
			edge.x_min = std::min(curr->x, next->x);
			edge.x = edge.x_min;
			const real_t y_min = std::min(curr->y, next->y);
			const real_t run = std::max(curr->x, next->x) - edge.x_min;
			const real_t rise = next->y - curr->y;
			if (rise != 0.0)
			{
				edge.slope_inv = run / rise;
				edge_bucket_t& bucket = edge_table[y_min];
				if (edge.slope_inv < 0.0)
				{
					// neg slope edges start at max x
					edge.x = edge.x_min + (edge.y_max - y_min) * -edge.slope_inv;
				}
				bucket.push_back(edge);
			}
		}
		// sort each edge in each bucket by x_min
		std::for_each(edge_table.begin(), edge_table.end(), [](auto edge_map_pair) -> void 
		{ 
			edge_bucket_t& edge_bucket = edge_map_pair.second;
			std::sort(edge_bucket.begin(), edge_bucket.end(), edge_sort()); 
		});
		scan_line2(edge_table, color);
	}

	/**
	 * Draw rectangle defined by corners p1 and p2.
	 */
	void draw_rect(const vector2f& p1, const vector2f& p2, const color_rgb& color)
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

	void set_pixel_row(const vector2ui& start, integer_t count, const color_rgb& color)
	{
		const uint8_t r = static_cast<uint8_t>(color[0] * 0xFF);
		const uint8_t g = static_cast<uint8_t>(color[1] * 0xFF);
		const uint8_t b = static_cast<uint8_t>(color[2] * 0xFF);
		size_t offset = ((start.y * dimension.x) + start.x) * 3;
		while (count > 0)
		{
			m_data[offset] = r;
			m_data[offset + 1] = g;
			m_data[offset + 2] = b;
			offset += 3;
			--count;
		}
	}
    
    const vector2ui dimension;
private:
    uint8_t* m_data;

	void midpoint_line(const vector2f& p1, const vector2f& p2, const color_rgb& color)
	{
		const real_t dx = p2.x - p1.x;
		const real_t dy = p2.y - p1.y;
		real_t d = 2.0 * dy - dx;
		const real_t incrE = 2.0 * dy;
		const real_t incrNE = 2.0 * (dy - dx);
		real_t x = p1.x;
		real_t y = p1.y;
		set_pixel(floor<size_t>({x,y}), color);

		while (x < p2.x)
		{
			if (d <= 0.0)
			{
				d += incrE;
				x += 1.0;
			}
			else
			{
				d += incrNE;
				x += 1.0;
				y += 1.0;
			}
			set_pixel(floor<size_t>({ x,y }), color);
		}
	}
    
    /**
     * Graphic Gems 1 : Symmetric Double Step Line Algorithim
     */
    real_t absolute(real_t i, real_t j, real_t& k)
    {
        k = (i - j) < 0.0 ? -1.0 : 1.0;
        return (i - j) * k;
    }
    
    /* flag indicates the pixels needing swap back. */
    void plot(real_t x, real_t y, bool flag, const color_rgb& color)
    {
        if (flag)
            set_pixel(floor<size_t>({ y,x }), color);
        else
            set_pixel(floor<size_t>({ x,y }), color);
    }
    
    // a == x, b == y
    void symwuline(const vector2f p1, const vector2f& p2, const color_rgb& color)
    {
        real_t sign_x, sign_y;
        real_t dx = absolute(p2.x, p1.x, sign_x);
        real_t dy = absolute(p2.y, p1.y, sign_y);
        real_t step = 0.0;
        // decide increment sign by slope sign
        if(sign_x == sign_y)
        {
            step = 1;
        }
        else
        {
            step = -1.0;
        }
        if(dx == 0.0)
        {
            real_t y = p1.y;
            real_t endy = p2.y;
            real_t inc = 1.0;
            if(p1.y > p2.y)
            {
                std::swap(y, endy);
            }
            do
            {
                plot(p1.x, y, false, color);
                y += inc;
            } while(y < endy);
            plot(p1.x, endy, false, color);
            return;
        }
        // choose axis of greatest movement
        vector2f v1,v2;
        const bool reverse = dy > dx;
        if(reverse)
        {
            v1 = p2;
            v2 = p1;
            std::swap(dx,dy);
        }
        else
        {
            v1 = p1;
            v2 = p2;
        }
        real_t x, y, x1, y1;
        if(v1.x > v2.x)
        {
            x = v2.x;
            y = v2.y;
            x1 = v1.x;
            y1 = v1.y;
        }
        else
        {
            x = v1.x;
            y = v1.y;
            x1 = v2.x;
            y1 = v2.y;
        }
        
        /* Note dx=n implies 0 - n or (dx+1) pixels to be set */
        /* Go round loop dx/4 times then plot last 0,1,2 or 3 pixels */
        /* In fact (dx-1)/4 as 2 pixels are already plotted */
        const integer_t xend = static_cast<integer_t>(std::floor(dx - 1.0)) / 4;
        const integer_t pixels_left = static_cast<integer_t>(std::floor(dx - 1.0)) % 4; /* number of pixels left over at the end */
        
        plot(x, y, reverse, color);
        if(pixels_left < 0) return;
        
        plot(x1, y1, reverse, color);
        real_t incr2 = 4.0 * dy - 2.0 * dx;
        if(incr2 < 0.0) // slope less than 1/2
        {
            real_t c = 2.0 * dy;
            real_t incr1 = 2.0 * c;
            real_t D = incr1 - dx;
            for(integer_t i = 0; i < xend; ++i)
            {
                ++x;
                --x1;
                if(D < 0.0)
                {
                    // pattern 1 forwards
                    plot(x, y, reverse, color);
                    plot(++x, y, reverse, color);
                    // pattern 1 backwards
                    plot(x1, y1, reverse, color);
                    plot(--x1, y1, reverse, color);
                    D += incr1;
                }
                else
                {
                    if (D < c)
                    {
                        // pattern 2 forwards
                        plot(x, y, reverse, color);
                        plot(++x, y += step, reverse, color);
                        // pattern 2 backwards
                        plot(x1, y1, reverse, color);
                        plot(--x1, y1 -= step, reverse, color);
                    }
                    else
                    {
                        // pattern 3 forwards
                        plot(x, y += step, reverse, color);
                        plot(++x, y, reverse, color);
                        // pattern 3 backwards
                        plot(x1, y1 -= step, reverse, color);
                        plot(--x1, y1, reverse, color);
                    }
                    D += incr2;
                }
            }
            // plot last pattern
            if(pixels_left)
            {
                if(D < 0.0)
                {
                    plot(++x, y, reverse, color); // pattern 1
                    if(pixels_left > 1)
                    {
                        plot(++x, y, reverse, color);
                    }
                    if(pixels_left > 2)
                    {
                        plot(--x1, y1, reverse, color);
                    }
                }
                else
                {
                    if(D < c)
                    {
                        plot(++x, y, reverse, color);	// pattern 2
                        if(pixels_left > 1)
                        {
                            plot(++x, y += step, reverse, color);
                        }
                        if(pixels_left > 2)
                        {
                            plot(--x1, y1, reverse, color);
                        }
                    }
                    else
                    {
                        plot(++x, y += step, reverse, color);	// pattern 3
                        if(pixels_left > 1)
                        {
                            plot(++x, y, reverse, color);
                        }
                        if(pixels_left > 2)
                        {
                            plot(--x1, y1 -= step, reverse, color);
                        }
                    }
                }
            }
        }
        else // slope greater than 1/2
        {
            real_t c = 2.0 * (dy - dx);
            real_t incr1 = 2.0 * c;
            real_t D = incr1 + dx;
            for(integer_t i = 0; i < xend; ++i)
            {
                ++x;
                --x1;
                if(D > 0.0)
                {
                    // pattern 4 forwards
                    plot(x, y += step, reverse, color);
                    plot(++x, y += step, reverse, color);
                    // pattern 4 backwards
                    plot(x1, y1 -= step, reverse, color);
                    plot(--x1, y1 -= step, reverse, color);
                    D += incr1;
                }
                else
                {
                    if (D < c)
                    {
                        // pattern 2 forwards
                        plot(x, y, reverse, color);
                        plot(++x, y += step, reverse, color);
                        // pattern 2 backwards
                        plot(x1, y1, reverse, color);
                        plot(--x1, y1 -= step, reverse, color);
                    }
                    else
                    {
                        // pattern 3 forwards
                        plot(x, y += step, reverse, color);
                        plot(++x, y, reverse, color);
                        // pattern 3 backwards
                        plot(x1, y1 -= step, reverse, color);
                        plot(--x1, y1, reverse, color);
                    }
                    D += incr2;
                }
            }
            // plot last pattern
            if(pixels_left)
            {
                if(D > 0.0)
                {
                    plot(++x, y += step, reverse, color); // pattern 4
                    if(pixels_left > 1)
                    {
                        plot(++x, y += step, reverse, color);
                    }
                    if(pixels_left > 2)
                    {
                        plot(--x1, y1 -= step, reverse, color);
                    }
                }
                else
                {
                    if(D < c)
                    {
                        plot(++x, y, reverse, color);	// pattern 2
                        if(pixels_left > 1)
                        {
                            plot(++x, y += step, reverse, color);
                        }
                        if(pixels_left > 2)
                        {
                            plot(--x1, y1, reverse, color);
                        }
                    }
                    else
                    {
                        plot(++x, y += step, reverse, color);	// pattern 3
                        if(pixels_left > 1)
                        {
                            plot(++x, y, reverse, color);
                        }
                        if(pixels_left > 2)
                        {
                            if(D > c)
                            {
                                plot(--x1, y1 -= step, reverse, color); // step 3
                            }
                            else
                            {
                                plot(--x1, y1, reverse, color); // step 2
                            }
                        }
                    }
                }
            }
        }
    }
    
    // Bresenham’s algorithm (1965)
    // Graphic Gems 1 II.8
    integer_t sgn(real_t x)
    {
        return x > 0.0 ? 1.0 : -1.0;
    }
    
    void digline(const vector2f& p1, const vector2f& p2, const color_rgb& color)
    {
        const real_t dx = p2.x - p1.x;
        const real_t dy = p2.y - p1.y;
        const real_t ax = std::abs(dx)*2.0;
        const real_t ay = std::abs(dy)*2.0;
        const real_t sx = sgn(dx);
        const real_t sy = sgn(dy);
        real_t x = p1.x;
        real_t y = p1.y;
        real_t d = 0.0;
        if(ax > ay) // x dominant
        {
            d = ay - ax / 2.0;
            while(true)
            {
                set_pixel(floor<size_t>({ x,y }), color);
                if (x >= p2.x) return;
                if(d >= 0.0)
                {
                    y += sy;
                    d -= ax;
                }
                x += sx;
                d += ay;
            }
        }
        else
        {
            d = ax - ay / 2.0;
            while(true)
            {
                set_pixel(floor<size_t>({ x,y }), color);
                if (y >= p2.y) return;
                if(d >= 0.0)
                {
                    x += sx;
                    d -= ay;
                }
                y += sy;
                d += ax;
            }
        }
    }

	void scan_line(const vector2f& p1, const vector2f& p2, const color_rgb& color)
	{
		using edge_bucket_t = std::vector<edge_t>;
		using edge_table_t = std::map<real_t, edge_bucket_t>;
		using active_edge_table_t = std::list<edge_t>;

		const real_t y_max = std::max(p1.y, p2.y);
		edge_table_t edge_table;
		edge_bucket_t edge_bucket;
		edge_t left_edge, right_edge;
		left_edge.x = left_edge.x_min = std::min(p1.x, p2.x);
		right_edge.x = right_edge.x_min = std::max(p1.x, p2.x);
		right_edge.y_max = left_edge.y_max = std::max(p1.y, p2.y);
		right_edge.slope_inv = left_edge.slope_inv = 0.0;
		edge_bucket.push_back(left_edge);
		edge_bucket.push_back(right_edge);
		std::sort(edge_bucket.begin(), edge_bucket.end(), edge_sort());
		edge_table[std::min(p1.y, p2.y)] = edge_bucket;

		active_edge_table_t active_edge_table;
		edge_table_t::const_iterator et_itr = edge_table.begin();
		real_t y_cur = et_itr->first;
		while (!edge_table.empty() || !active_edge_table.empty())
		{
			if (edge_table.count(y_cur))
			{
				for (const edge_t& edge : edge_table[y_cur])
				{
					active_edge_table.push_back(edge);
				}
			}
			std::remove_if(active_edge_table.begin(), active_edge_table.end(), [y_cur](const edge_t& edge) -> bool { return edge.y_max <= y_cur;  });
			//std::sort(active_edge_table.begin(), active_edge_table.end(), edge_sort);
			active_edge_table.sort(edge_sort());

			active_edge_table_t::const_iterator left_edge, right_edge;
			left_edge = active_edge_table.begin();
			while(left_edge != active_edge_table.end())
			{
				right_edge = left_edge;
				++right_edge;
				set_pixel_row(floor<size_t>({ left_edge->x, y_cur }), std::floor(right_edge->x - left_edge->x), color);
				std::advance(left_edge, 2);
			}
			y_cur += 1.0;
			if (y_cur > y_max) break;
			std::for_each(active_edge_table.begin(), active_edge_table.end(), [](edge_t& edge) { if (edge.slope_inv != 0.0) edge.x += edge.slope_inv; });
		}
	}

	void scan_line2(const edge_table_t& edge_table, const color_rgb& color)
	{
		// todo: this should be done earlier
		real_t y_max = 0.0;
		for (auto bucket_pair : edge_table)
		{
			for (const edge_t& edge : bucket_pair.second)
			{
				y_max = std::max(y_max, edge.y_max);
			}
		}
		//real_t y_max = edge_table.rbegin()->first;
		active_edge_table_t active_edge_table;
		edge_table_t::const_iterator et_itr = edge_table.begin();
		real_t y_cur = et_itr->first;
		while (!edge_table.empty() || !active_edge_table.empty())
		{
			edge_table_t::const_iterator itr = edge_table.find(y_cur);
			if (itr != edge_table.end())
			{
				for (const edge_t& edge : itr->second)
				{
					active_edge_table.push_back(edge);
				}
			}
			std::remove_if(active_edge_table.begin(), active_edge_table.end(), [y_cur](const edge_t& edge) -> bool { return edge.y_max <= y_cur;  });
			active_edge_table.sort(edge_sort());

			active_edge_table_t::const_iterator left_edge, right_edge;
			left_edge = active_edge_table.begin();
			while (left_edge != active_edge_table.end())
			{
				right_edge = left_edge;
				++right_edge;
				set_pixel_row(floor<size_t>({ left_edge->x, y_cur }), std::floor(right_edge->x - left_edge->x), color);
				std::advance(left_edge, 2);
			}
			y_cur += 1.0;
			if (y_cur > y_max) break;
			std::for_each(active_edge_table.begin(), active_edge_table.end(), [](edge_t& edge) { if (edge.slope_inv != 0.0) edge.x += edge.slope_inv; });
		}
	}
};
}