#include "Film.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>


Flim::Film(int w, int h, const char* filename){
	width = w;
	height = h;
	filename = filename;

	image = new std::vector<unsigned char>();
}

Film::~Film(){

}

void Film::encode(){
	unsigned error = lodepng::encode(filename, image, width, height);

	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

void Film::addPixel(const Sample& s, const Color& color){
	image.add(color.getRed());
	image.add(color.getBlue());
	image.add(color.getGreen());
	image.add(color.getAlpha());
}