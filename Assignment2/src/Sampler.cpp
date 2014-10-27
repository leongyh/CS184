#include "Sampler.h"
#include <cstdlib>
#include <cstdio>

Sampler::Sampler(int w, int h, float l, float r, float t, float b){
	this->width = w;
	this->height = h;

	this->l = l;
	this->r = r;
	this->t = t;
	this->b = b;

	this->iter = w * h - 1;
}

Sampler::~Sampler(){

}

//Simple, no AA routine
Sample* Sampler::sampleNext(){
	int i = iter % width;
	int j = height - (iter / width);

	float u = l + (r - l) * (i + 0.5) / width;
	float v = b + (t - b) * (j + 0.5) / height;

	Sample* s = new Sample(i, j, u, v);

	iter--;

	return s;
}

bool Sampler::hasNext(){
	if (iter < 0){
		return false;
	} else{
		return true;
	}
}

void Sampler::print(){
	printf("The Sampler has (width, height): (%d, %d)\n", width, height);
}