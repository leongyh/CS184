#ifndef RAY_H_
#define RAY_H_

#include <glm/glm.hpp>

class Ray{
	glm::vec3 position;
	glm::vec3 direction;
	static const float t_min = 0.0f;
	static const float t_max = 999.0f;

	public:
		Ray(float px, float py, float pz, float dx, float dy, float dz);
		virtual ~Ray();

		glm::vec3 getPosition();
		glm::vec3 getDirection();
		
		void print();
};

#endif