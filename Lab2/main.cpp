#include <iostream>
#include <cstdlib>
#include <Magick++.h>
#include <memory>
#include <random>


const size_t width = 100;
const size_t height = 100;
const size_t pixelDepth = 3;


//void setPixel(size_t _x, size_t _y, unsigned char _r, unsigned char _g, unsigned char _b, std::unique_ptr<unsigned char []> &_image) // raw data for the image not copy
//{
//    auto offset = (_y*width*3)+(_x*3); // or  _x*height*3 + _y*3 or _y*width*3 + _x*3
//    _image[offset] = _r;
//    _image[offset+1] = _g;
//    _image[offset+2] = _b;
//}



//void clearScreen(char _r, char _g, char _b, std::unique_ptr<unsigned char []> &_image)
//{
//    for(size_t i=0; i< width; i++)
//    {
//        for(size_t j=0; j<height; j++)
//        {
//            setPixel(i, j, _r, _g, _b, _image);
//        }
//    }
//}


int main()
{

    std::random_device rd;
    std::mt19937 gen(rd()); // now we got a generator
    std::uniform_int_distribution<> colour(0,255);


    std::unique_ptr<unsigned char []> image =
            std::make_unique<unsigned char []>(width * height * pixelDepth); //all + // dynamic array in heap - auto garbage cleanup after scope ending

    //
    auto setPixel = [&image](size_t _x, size_t _y, unsigned char _r, unsigned char _g, unsigned char _b) //[] captcha read write, () parameters inputs
    {
        auto offset = (_y*width*3)+(_x*3); // or  _x*height*3 + _y*3 or _y*width*3 + _x*3
        image[offset] = _r;
        image[offset+1] = _g;
        image[offset+2] = _b;
    };

//    for(size_t i=0; i<width*height*pixelDepth; ++i)
//    {
//        image[i] = 255;  // bg colour 255 - white 0 - black
//    }

//    for(size_t j=0; j<width; ++j)
//    {
//        setPixel(j,j,255,0,0,image);  // setting 1st diagonal shape from top left to right
//        setPixel(width-j,j, 0,255,0,image); // setting 2nd diagonal shape from bottom left to right
//    }

    //char *fileName="image.%03d.bmp" ; // zero padding
    char fileName[20];

    for(size_t frame = 0; frame < 100; ++frame)
    {

        for(size_t y=0; y<height; ++y)
            for(size_t x=0; x<width; ++x)
                setPixel(x,y, colour(gen), colour(gen), colour(gen));   // ()%255 -- this rand is terrible

        //clearScreen(255, 0, 255,);

        //setPixel (width-1,0,255,0,0, image); // set each pixel
        sprintf(fileName, "image.%03d.bmp", frame); //formated printf, copy this string .bmp, with this changing var
        Magick::Image output(width, height, "RGB", Magick::CharPixel, image.get());
        output.depth(16);
        std::cerr<<"Writing file" << fileName << '\n';
        output.write(fileName); // jpg tif and png not working atm


    }

    return EXIT_SUCCESS;
}
