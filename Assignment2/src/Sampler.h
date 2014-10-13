#ifndef SAMPLER_H_
#define SAMPLER_H_

#include <glm/glm.hpp>
#include "Sample.h"

class Sampler{
	int width;
	int height;

	float l, r;
	float t, b;

	int iter;

	public:
		Sampler(int w, int h, float l, float r, float t, float b);
		virtual ~Sampler();

		Sample* sampleNext();
		bool hasNext();

		void print();
};

#endif