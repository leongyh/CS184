#ifndef RAY_H_
#define RAY_H_

#include <glm/glm.hpp>

class Ray{
	glm::vec3 position;
	glm::vec3 direction;

	public:
		Ray(float px, float py, float pz, float dx, float dy, float dz);
		Ray(glm::vec3 point, glm::vec3 dir);
		virtual ~Ray();

		glm::vec3 getPosition();
		glm::vec3 getDirection();
		glm::vec3 getReverseDirection();
		glm::vec3 getPoint(float t);
		
		void print();
};

#endif