#ifndef SAMPLE_H_
#define SAMPLE_H_

#include <glm/glm.hpp>

class Sample{
	int i, j;
	float u, v;

	public:
		Sample(int i, int j, float u, float v);
		virtual ~Sample();

		int getI();
		int getJ();
		float getU();
		float getV();

		void print();
};

#endif