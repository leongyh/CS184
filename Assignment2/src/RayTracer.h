#ifndef RAY_TRACER_H_
#define RAY_TRACER_H_

#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <string>
#include "Sphere.h"
#include "Color.h"
#include "Ray.h"
#include "DirectionalLight.h"
#include "PointLight.h"

class RayTracer{
	public:
		RayTracer();
		virtual ~RayTracer();

		Color* traceSimple(Ray* cam_ray, std::vector<Sphere*>& spheres);
		Color* trace(Ray* cam_ray, std::vector<Sphere*>& spheres, std::vector<DirectionalLight*>& dir_lights, std::vector<PointLight*>& pnt_lights, int max_depth);

		void print();

	private:
		glm::vec3 traceRecursion(Ray* cam_ray, std::vector<Sphere*>& spheres, std::vector<DirectionalLight*>& dir_lights, std::vector<PointLight*>& pnt_lights, int max_depth, int current_depth);
		glm::vec3 calculateDiffusion(glm::vec3 normal, glm::vec3 incident, glm::vec3 intensity, glm::vec3 kd);
		glm::vec3 calculateSpecular(glm::vec3 normal, glm::vec3 incident, glm::vec3 intensity, glm::vec3 ks, int sp, Ray* view_ray);
		glm::vec3 calculateAmbient(glm::vec3 intensity, glm::vec3 ka);
};

#endif