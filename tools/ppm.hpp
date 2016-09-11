#pragma once

#include <cstdint>
#include <sstream>

namespace ross
{

/**
 * Write RGB24 buffer to PPM format
 **/
void ppm_write(std::ostream& os, const uint8_t* buf, size_t width, size_t height)
{
	std::ostringstream oss;
    oss << "P6\n" << width << " " << height << "\n" << "255" << "\n";
    os << oss.str();
    os.write(reinterpret_cast<const char*>(&buf[0]), width * height * 3);
}
    
}