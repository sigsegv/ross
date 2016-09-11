#include <iostream>
#include <fstream>
#include <ross/ross.hpp>
#include "../tools/ppm.hpp"

void example_1();
void example_2();
void write_canvas_to_disk(const ross::canvas& canvas, const std::string& ascii_out_path);

int main(int argc, char** argv)
{
    std::cout << "Welcome to Ross!\n";
    
    example_1();
    
    return 0;
}

void example_2()
{
    ross::canvas canvas({64,64});
    std::memset(canvas.data(), 0xFF, canvas.size());
    ross::color_rgb magenta{{1.0, 0.0, 1.0}};
    
    write_canvas_to_disk(canvas, "example2.ppm");
}

void example_1()
{
    // create 64x64 pixel surface
    // ross::surface_rgb24<64, 64> surface;
    // create canvas with surface
    // ross::canvas canvas;
    // draw horizontal line
    // canvas.moveto
    // canvas.lineto
    ross::canvas canvas({64,64});
    std::memset(canvas.data(), 0xFF, canvas.size());
    ross::color_rgb magenta{{1.0, 0.0, 1.0}};
    for(ross::integer_t x = 0; x < canvas.dimension.x; ++x)
    {
        canvas.set_pixel({x, x}, magenta);
    }
    write_canvas_to_disk(canvas, "example1.ppm");
}

void write_canvas_to_disk(const ross::canvas& canvas, const std::string& ascii_out_path)
{
    std::ofstream fout(ascii_out_path);
    ross::ppm_write(fout, canvas.data(), canvas.dimension.x, canvas.dimension.y);
}