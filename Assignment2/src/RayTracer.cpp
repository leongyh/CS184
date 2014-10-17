#include "RayTracer.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

RayTracer::RayTracer(){
	depth = 5;
}

RayTracer::RayTracer(int d){
	depth = d;
}

RayTracer::~RayTracer(){

}

Color* RayTracer::trace(Ray* cam_ray, std::vector<Sphere>& spheres){
	//find intersect on all geometries first
	Sphere* closest_sphere;
	float smallest_t = -1.0f;

	for(int i = 0; i < spheres.size(); i++){
		Sphere sphere = spheres[i];

		float t = sphere.intersect(cam_ray);

		if(t >= 0.0f){
			if(smallest_t < 0.0f){
				closest_sphere = &sphere;
				smallest_t = t;
			} else if(t < smallest_t){
				closest_sphere = &sphere;
				smallest_t = t;
			}
		}
	}

	//paint red for simple test
	if(smallest_t < 0.0f){
		return new Color(0.0f, 0.0f, 0.0f);
	} else{
		return new Color(1.0f, 0.0f, 0.0f);
	}
}

Color* RayTracer::trace(Ray* cam_ray, std::vector<Sphere>& spheres, std::vector<DirectionalLight>& dir_lights, std::vector<PointLight>& pnt_lights, std::map<std::string, glm::vec3>& shading_attr){
	//find intersect on all geometries first
	Sphere* closest_sphere;
	float smallest_t = -1.0f;

	for(int i = 0; i < spheres.size(); i++){
		Sphere sphere = spheres[i];

		float t = sphere.intersect(cam_ray);

		if(t >= 0.0f){
			if(smallest_t < 0.0f){
				closest_sphere = &sphere;
				smallest_t = t;
			} else if(t < smallest_t){
				closest_sphere = &sphere;
				smallest_t = t;
			}
		}
	}

	//for all rays that do not hit, paint black
	if(smallest_t < 0.0f){
		return new Color(0.0f, 0.0f, 0.0f);
	}

	//begin shading calculations
	glm::vec3 point = cam_ray->getPoint(smallest_t);
	glm::vec3 normal = closest_sphere->getNormal(point);

	//color components
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;

	for(int num_dl = 0; num_dl < dir_lights.size(); num_dl++){
		glm::vec3 incident = (dir_lights[num_dl]).getReverseDirection();
		glm::vec3 intensity = (dir_lights[num_dl]).getColor();

		Ray* dir_ray = new Ray(point, incident);

		for(int i = 0; i < spheres.size(); i++){
			Sphere sphere = spheres[i];

			float t = sphere.intersect(dir_ray);

			if(t >= 0.0f){
				if(smallest_t < 0.0f){
					closest_sphere = &sphere;
					smallest_t = t;
				} else if(t < smallest_t){
					closest_sphere = &sphere;
					smallest_t = t;
				}
			}
		}

		glm::vec3 rgbDiffusion = calculateDiffusion(normal, incident, intensity, shading_attr);

        glm::vec3 rgbSpecular = calculateSpecular(normal, incident, intensity, cam_ray, shading_attr);

        glm::vec3 rgbAmbient = calculateAmbient(intensity, shading_attr);

        r += rgbDiffusion.x + rgbSpecular.x + rgbAmbient.x;
        g += rgbDiffusion.y + rgbSpecular.y + rgbAmbient.y;
        b += rgbDiffusion.z + rgbSpecular.z + rgbAmbient.z;
	}

	for(int num_pl = 0; num_pl < pnt_lights.size(); num_pl++){
		glm::vec3 incident = (pnt_lights[num_pl]).getLightVec(point);
		glm::vec3 intensity = (pnt_lights[num_pl]).getColor();

		glm::vec3 rgbDiffusion = calculateDiffusion(normal, incident, intensity, shading_attr);

        glm::vec3 rgbSpecular = calculateSpecular(normal, incident, intensity, cam_ray, shading_attr);

        glm::vec3 rgbAmbient = calculateAmbient(intensity, shading_attr);

        r += rgbDiffusion.x + rgbSpecular.x + rgbAmbient.x;
        g += rgbDiffusion.y + rgbSpecular.y + rgbAmbient.y;
        b += rgbDiffusion.z + rgbSpecular.z + rgbAmbient.z;
	}

	r = std::min(1.0f, r);
	g = std::min(1.0f, g);
	b = std::min(1.0f, b);

	return new Color(r, g, b);
}

glm::vec3 RayTracer::calculateDiffusion(glm::vec3 normal, glm::vec3 incident, glm::vec3 intensity, std::map<std::string, glm::vec3>& shading_attr){
	float dot = glm::dot(normal, incident);

	float r = std::max(shading_attr["k_diffuse"].x * intensity.x * dot, 0.0f);
	float g = std::max(shading_attr["k_diffuse"].y * intensity.y * dot, 0.0f);
	float b = std::max(shading_attr["k_diffuse"].z * intensity.z * dot, 0.0f);

	return glm::vec3(r, g, b);
}

glm::vec3 RayTracer::calculateSpecular(glm::vec3 normal, glm::vec3 incident, glm::vec3 intensity, Ray* view_ray, std::map<std::string, glm::vec3>& shading_attr){
	//reflected
	glm::vec3 r_vec = glm::normalize((-1.0f * incident) + (2.0f * glm::dot(incident, normal) * normal));
	float dot_pow = pow(std::max(0.0f, glm::dot(r_vec, view_ray->getReverseDirection())), (int) shading_attr["pow_specular"].x);

	//half-angle
	// glm::vec3 h_vec = glm::normalize(incident + view_ray->getReverseDirection());
 	// float dot_pow = pow(std::max(0.0f, glm::dot(normal, h_vec)), (int) shading_attr["pow_specular"].x);

	float r = std::max(shading_attr["k_specular"].x * intensity.x * dot_pow, 0.0f);
	float g = std::max(shading_attr["k_specular"].y * intensity.y * dot_pow, 0.0f);
	float b = std::max(shading_attr["k_specular"].z * intensity.z * dot_pow, 0.0f);

	return glm::vec3(r, g, b);
}

glm::vec3 RayTracer::calculateAmbient(glm::vec3 intensity, std::map<std::string, glm::vec3>& shading_attr){
	float r = std::max(shading_attr["k_ambient"].x * intensity.x , 0.0f);
	float g = std::max(shading_attr["k_ambient"].y * intensity.y, 0.0f);
	float b = std::max(shading_attr["k_ambient"].z * intensity.z, 0.0f);

	return glm::vec3(r, g, b);
}

void RayTracer::print(){
	printf("The Ray Tracer has recursion depth %d", depth);
}