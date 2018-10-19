cmake_minimum_required(VERSION 3.5)

# this sets the project create project
project(ImageWriter)

# adding sub components libs
find_package(ImageMagick COMPONENTS Magick++)

#add keywords, -I line, includes
include_directories(/public/devel/2018/include/ImageMagick-7)

#c++ VERSION
set(CMAKE_CXX_STANDARD 17)

#adds all sources, adding main
set(SOURCES main.cpp)

#ImageWriter - linking all source files , adding lib, craete executable
add_executable(ImageWriter ${SOURCES})

# image libs are taken from COMPONENTS line
target_link_libraries(ImageWriter ${ImageMagick_LIBRARIES})