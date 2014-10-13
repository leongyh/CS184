#ifndef FILM_H_
#define FILM_H_

#include <glm/glm.hpp>
#include "lodepng.h"
#include "Sample.h"
#include "Color.h"

class Film{
	int width;
	int height;
	const char* filename;

	std::vector<unsigned char> image;

	public:
		Film(int w, int h, const char* f);
		virtual ~Film();

		void encode();
		void encodeTest();
		void addPixel(Sample* s, Color* color);
};

#endif