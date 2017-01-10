#include <iostream>
#include <fstream>
#include <ross/ross.hpp>
#include "../tools/ppm.hpp"

void example_1();
void example_2();
void example_3();
void example_4();
void example_5();
void write_canvas_to_disk(const ross::canvas& canvas, const std::string& ascii_out_path);

const ross::color_rgb magenta{ { 1.0, 0.0, 1.0 } };
const ross::color_rgb yellow{ { 1.0, 1.0, 0.0 } };
const ross::color_rgb cyan{ { 0.0, 1.0, 1.0 } };
const ross::color_rgb black{ { 0.0, 0.0, 0.0 } };

int main(int argc, char** argv)
{
    std::cout << "Welcome to Ross!\n";
    
    example_1();
	example_2();
	example_3();
	example_4();
	example_5();
    
    return 0;
}

void example_5()
{
	ross::canvas canvas({ 64,64 });
	std::memset(canvas.data(), 0xFF, canvas.size());

	std::vector<ross::vector2f> triangle = { { 12.0, 60.0 },{ 32.0, 4.0 },{ 52.0, 60.0 } };
	canvas.fill_path(triangle, magenta);
	std::vector<ross::vector2f> arrow = { { 28.0, 20.0 },{ 28.0, 40.0 },{ 22.0, 40.0 },{32.0,50.0},{42.0, 40.0},{36.0, 40.0},{36.0,20.0} };
	canvas.fill_path(arrow, cyan);

	write_canvas_to_disk(canvas, "example5.ppm");
}

void example_4()
{
	ross::canvas canvas({ 64,64 });
	std::memset(canvas.data(), 0xFF, canvas.size());

	std::vector<ross::vector2f> path = { {15.0, 15.0}, {15.0, 45.0}, {45.0, 45.0}, {45.0, 15.0} };
	canvas.fill_path(path, magenta);

	write_canvas_to_disk(canvas, "example4.ppm");
}

void example_3()
{
	ross::canvas canvas({ 64,64 });
	std::memset(canvas.data(), 0xFF, canvas.size());

	canvas.draw_rect({ 15.0, 15.0 }, { 45.0, 45.0 }, magenta);

	write_canvas_to_disk(canvas, "example3.ppm");
}

void example_2()
{
    ross::canvas canvas({64,64});
    std::memset(canvas.data(), 0xFF, canvas.size());

	canvas.draw_line({ 0.0, 24.0 }, { 64.0, 44.0 }, magenta);
    canvas.draw_line({ 0.0, 0.0 }, { 64.0, 64.0 }, magenta);
    canvas.draw_line({ 64.0, 24.0 }, { 0.0, 44.0 }, cyan);
    //canvas.draw_line({ 0.0, 64.0 }, { 64.0, 0.0 }, cyan);
    canvas.draw_line({ 32.0, 0.0 }, { 32.0, 64.0 }, yellow);
    canvas.draw_line({ 0.0, 32.0 }, { 64.0, 32.0 }, black);
    
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
    ross::canvas canvas({64, 64});
    std::memset(canvas.data(), 0xFF, canvas.size());
    ross::color_rgb magenta{{1.0, 0.0, 1.0}};
    for(ross::size_t x = 0; x < canvas.dimension.x; ++x)
    {
        canvas.set_pixel({x, x}, magenta);
    }	
    write_canvas_to_disk(canvas, "example1.ppm");
}

void write_canvas_to_disk(const ross::canvas& canvas, const std::string& ascii_out_path)
{
    std::ofstream fout(ascii_out_path, std::ios::binary);
    ross::ppm_write(fout, canvas.data(), canvas.dimension.x, canvas.dimension.y);
}