#include <glm/glm.hpp>

class Sphere{
	glm::vec3 position
	float radius;

	public:
		Sphere(float x, float y, float z, float r);
		virtual ~Sphere();

		void print();
};