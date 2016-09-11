#include <array>
#include <fstream>

#include "catch.hpp"
#include "../tools/ppm.hpp"

TEST_CASE( "Generate 64x64 Magenta PPM File", "[ppm]" )
{
    constexpr size_t width = 64;
    constexpr size_t height = 64;
    typedef std::array<uint8_t, width * height * 3> ppm_buf_t;
    ppm_buf_t buf;
    buf.fill(0x77);
    ppm_buf_t::iterator itr = buf.begin();
    ppm_buf_t::iterator end = buf.end();
    while(itr != end)
    {
        *itr = 0xFF;
        ++itr;
        *itr = 0x00;
        ++itr;
        *itr = 0xFF;
        ++itr;
    }
    
    std::ofstream fout("magenta.ppm");
    
    ross::ppm_write(fout, buf.data(), width, height);
    
    REQUIRE( true ); // not an actual unit test... need to open ppm in viewer, like Gimp.
    
    fout.close();
}
