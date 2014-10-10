#include "Film.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>


Flim::Film(float w, float h){
	width = w;
	height = h;

	samples = new std::vector<Sample>();
}

Film::~Film(){

}

void Film::encodeImage(){

}

void Film::addSample(Sample s){
	samples.add(s);
}