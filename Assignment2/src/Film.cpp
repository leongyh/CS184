#include "Film.h"
#include <cstdlib>
#include <cstdio>

Film::Film(int w, int h, const char* f){
	width = w;
	height = h;
	filename = f;

	image.reserve(width * h * 4);
}

Film::~Film(){

}

void Film::encode(){
	unsigned error = lodepng::encode(filename, image, width, height);

	// unsigned error = lodepng::encode(filename, image, width, height);

	if(error) printf("%s", lodepng_error_text(error));
}

void Film::addPixel(Sample* s, Color* color){
	image.push_back(color->getRed());
	image.push_back(color->getBlue());
	image.push_back(color->getGreen());
	image.push_back(color->getAlpha());
}