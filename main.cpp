#include <iostream>
#include <cstdlib>
#include <Magick++.h>
#include <memory>

int main()
{
    const size_t width = 400;
    const size_t height = 400;
    const size_t pixelDepth = 3;
    std::unique_ptr<unsigned char []> image =
            std::make_unique<unsigned char []>(width * height * pixelDepth); // all + // dynamic array in heap

    for(size_t i=0; i<width*height*pixelDepth; ++i)
    {
        image[i] = 128;
    }

    Magick::Image output(width, height, "RGB", Magick::CharPixel, image.get());
    output.write("test.bmp"); // jpg tif and png not working atm

    return EXIT_SUCCESS;
}
