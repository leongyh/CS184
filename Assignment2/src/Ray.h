#include <glm/glm.hpp>

class Ray{
	glm::vec3 position;
	glm::vec3 direction;
	float t_min = 0;
	float t_max = 999;

	public:
		Ray(float px, float py, float pz, float dx, float dy, float dz);
		virtual ~Ray();

		glm::vec3 getPosition();
		glm::vec3 getDirection();
		
		void print();
};