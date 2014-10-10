#include "Sampler.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>


Sampler::Sampler(float w, float h){
	width = w;
	height = h;

	iter = 0;
}

Sampler::~Sampler(){

}

Sample Sampler::sampleNext(){
	int u = iter % width;
	int v = iter / height;

	Sample s = new Sample()
}

void Sampler::print(){
	printf("The Sampler has (width, height): (%f,%f)", width, height);
}