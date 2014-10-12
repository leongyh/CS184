#include "Sampler.h"
#include <cstdlib>
#include <cstdio>

Sampler::Sampler(int w, int h, float l, float r, float t, float b){
	width = w;
	height = h;

	l = l;
	r = r;
	t = t;
	b = b;

	iter = 0;
	max_iter = w*h;
}

Sampler::~Sampler(){

}

//Simple, no AA routine
Sample* Sampler::sampleNext(){
	int i = iter % width;
	int j = iter / height;

	float u = l + (r - l) * (i + 0.5) / width;
	float v = b + (t - b) * (j + 0.5) / height;

	Sample* s = new Sample(i, j, u, v);

	iter++;

	return s;
}

bool Sampler::hasNext(){
	if (iter >= max_iter){
		return false;
	} else{
		return true;
	}
}

void Sampler::print(){
	printf("The Sampler has (width, height): (%d, %d)", width, height);
}