#include <glm/glm.hpp>
#include "Camera.h"
#include "Sphere.h"
#include "Color.h"

class RayTracer{
	int depth;

	public:
		RayTracer();
		RayTracer(int d);
		virtual ~RayTracer();

		Color trace(const Ray& cam_ray, std::vector<Sphere> spheres);

		void print();
};