#ifndef COLOR_H_
#define COLOR_H_

#include <glm/glm.hpp>

class Color{
	glm::vec3 rgb;
	float alpha;

	public:
		Color(float r, float g, float b);
		Color(glm::vec3 col);
		virtual ~Color();

		// void addRGB(float r, float g, float b);
		unsigned char getRed();
		unsigned char getBlue();
		unsigned char getGreen();
		unsigned char getAlpha();

		void print();
};

#endif