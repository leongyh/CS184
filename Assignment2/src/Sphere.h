#include <glm/glm.hpp>

class Sphere{
	glm::vec3 position
	float radius;

	public:
		Sphere(float x, float y, float z, float r);
		virtual ~Sphere();

		glm::vec3 getNormal(glm::vec3 point);
		float intersect(const Ray& cam_ray);

		void print();
};