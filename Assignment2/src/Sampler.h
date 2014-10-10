#include <glm/glm.hpp>
#include "Sample.h"

class Sampler{
	int width;
	int height;

	int iter;

	public:
		Sampler(float w, float h);
		virtual ~Sampler();

		Sample sampleNext();

		void print();
};