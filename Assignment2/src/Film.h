#ifndef FILM_H_
#define FILM_H_

#include <glm/glm.hpp>
#include "lodepng.h"
#include "Sample.h"
#include "Color.h"

class Film{
	int width;
	int height;
	std::string filename;

	std::vector<unsigned char> image;

	public:
		Film(int w, int h, const std::string f);
		virtual ~Film();

		void encode();
		void encodeTest();
		void addPixel(Sample* s, Color* color);
		void print();
};

#endif