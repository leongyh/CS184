#include <glm/glm.hpp>
#include <lodepng>
#include "Sample.h"
#include "Color.h"

class Film{
	int width;
	int height;
	char* filename;

	std::vector<unsigned char> image;

	public:
		Film(float w, float h, const char* filename);
		virtual ~Film();

		void encode();
		void addPixel(const Sample& s, const Color& color);
};