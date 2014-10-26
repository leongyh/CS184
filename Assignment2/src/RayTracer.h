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
	int depth;

	public:
		RayTracer();
		RayTracer(int d);
		virtual ~RayTracer();

		Color* trace(Ray* cam_ray, std::vector<Sphere>& spheres);
		Color* trace(Ray* cam_ray, std::vector<Sphere>& spheres, std::vector<DirectionalLight>& dir_lights, std::vector<PointLight>& pnt_lights, std::map<std::string, glm::vec3>& shading_attr);

		void print();

	private:
		glm::vec3 calculateDiffusion(glm::vec3 normal, glm::vec3 incident, glm::vec3 intensity, std::map<std::string, glm::vec3>& shading_attr);
		glm::vec3 calculateSpecular(glm::vec3 normal, glm::vec3 incident, glm::vec3 intensity, Ray* view_ray, std::map<std::string, glm::vec3>& shading_attr);
		glm::vec3 calculateAmbient(glm::vec3 intensity, std::map<std::string, glm::vec3>& shading_attr);
};

#endif