#ifndef SPHERE_H_
#define SPHERE_H_

#include <glm/glm.hpp>
#include "Ray.h"

class Sphere{
	glm::vec3 position;
	float radius;

	public:
		Sphere(float x, float y, float z, float r);
		Sphere(const Sphere& obj);
		virtual ~Sphere();

		glm::vec3 getNormal(glm::vec3 point);
		float intersect(Ray* cam_ray);

		void print();
};

#endif