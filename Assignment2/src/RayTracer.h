#ifndef RAY_TRACER_H_
#define RAY_TRACER_H_

#include <glm/glm.hpp>
#include <vector>
#include "Sphere.h"
#include "Color.h"
#include "Ray.h"

class RayTracer{
	int depth;

	public:
		RayTracer();
		RayTracer(int d);
		virtual ~RayTracer();

		Color* trace(Ray* cam_ray, std::vector<Sphere>& spheres);

		void print();
};

#endif