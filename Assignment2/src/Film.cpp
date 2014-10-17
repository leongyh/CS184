#include "Film.h"
#include <cstdlib>
#include <cstdio>

Film::Film(int w, int h, const char* f){
	this->width = w;
	this->height = h;
	this->filename = f;

	this->image.reserve(width * h * 4);
}

Film::~Film(){

}

void Film::encode(){
	unsigned error = lodepng::encode(filename, image, width, height);

	// unsigned error = lodepng::encode(filename, image, width, height);

	if(error) printf("%s", lodepng_error_text(error));
}

void Film::addPixel(Sample* s, Color* color){
	this->image.push_back(color->getRed());
	this->image.push_back(color->getBlue());
	this->image.push_back(color->getGreen());
	this->image.push_back(color->getAlpha());
}

void Film::encodeTest(){
	for(int i = width*height; i > 0; i--){
		if(i < width*height/2){
			this->image.push_back(0);
			this->image.push_back(0);
			this->image.push_back(0);
			this->image.push_back(255);
		}else{
			this->image.push_back(255);
			this->image.push_back(255);
			this->image.push_back(255);
			this->image.push_back(255);
		}
	}
	

	unsigned error = lodepng::encode(filename, image, width, height);

	if(error) printf("%s", lodepng_error_text(error));	
}