#include <glm/glm.hpp>

class Sample{
	float x;
	float y;
	glm::vec3 color;

	public:
		Sample(float x, float y);
		virtual ~Sample();

		void addSample();
		glm::vec3 Sample::getColor();
		float Sample::getX();
		float Sample::getY();
};