#include <glm/glm.hpp>

class Color{
	glm::vec3 rgb;
	float alpha;

	public:
		Color(float r, float g, float b,);
		virtual ~Color();

		unsigned char getRed();
		unsigned char getBlue();
		unsigned char getGreen();
		unsigned char getAlpha();

		void print()
};