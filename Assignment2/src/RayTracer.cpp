#define GLM_SWIZZLE

#include "RayTracer.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

RayTracer::RayTracer(){
}

RayTracer::~RayTracer(){

}

Color* RayTracer::traceSimple(Ray* cam_ray, std::vector<Sphere*>& spheres){
	//find intersect on all geometries first
	Sphere* closest_sphere;
	float smallest_t = -1.0f;

	for(int i = 0; i < spheres.size(); i++){
		Sphere* sphere = spheres[i];

		float t = sphere->intersect(cam_ray);

		if(t >= 0.0f){
			if(smallest_t < 0.0f){
				closest_sphere = sphere;
				smallest_t = t;
			} else if(t < smallest_t){
				closest_sphere = sphere;
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

glm::vec3 RayTracer::traceRecursion(Ray* cam_ray, std::vector<Sphere*>& spheres, std::vector<DirectionalLight*>& dir_lights, std::vector<PointLight*>& pnt_lights, int max_depth, int current_depth){
	// printf("%s\n", "Start");

	//find intersect on all geometries first
	Sphere* closest_sphere;
	float smallest_t = -1.0f;

	for(int i = 0; i < spheres.size(); i++){
		Sphere* sphere = spheres[i];

		float t = sphere->intersect(cam_ray);

		if(t >= 0.0f){
			if(smallest_t < 0.0f){
				closest_sphere = sphere;
				smallest_t = t;
			} else if(t < smallest_t){
				closest_sphere = sphere;
				smallest_t = t;
			}
		}
	}
	
	//for all rays that do not hit, paint black
	if(smallest_t < 0.0f){
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}

	//begin shading calculations
	glm::vec3 point = cam_ray->getPoint(smallest_t);
	glm::vec3 normal = closest_sphere->getNormal(point);

	if(closest_sphere->isTransformed()){
		glm::mat4 t_mat = closest_sphere->getTransform();
		glm::vec4 temp_point = glm::vec4(point, 0.0f);

		temp_point = t_mat * temp_point;

		point = temp_point.xyz();
	}

	
	// closest_sphere->print();
	// printf("%f %f %f\n", point.x, point.y, point.z);

	//color components
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;

	for(int num_dl = 0; num_dl < dir_lights.size(); num_dl++){
		glm::vec3 incident = (dir_lights[num_dl])->getReverseDirection();
		glm::vec3 intensity = (dir_lights[num_dl])->getColor();

		// //find shadows, skip iteration
		Ray* shadow_ray = new Ray(point, incident);
		bool isShadowed = false;

		for(int i = 0; i < spheres.size(); i++){
			Sphere* sphere = spheres[i];

			float t = sphere->intersect(shadow_ray);

			if(t > 0.0f){
				// delete dir_ray;
				isShadowed = true;
				break;
			} else if(closest_sphere == sphere){
				continue;
			}
		}

		// delete dir_ray;

		if(isShadowed){
	        glm::vec3 rgbAmbient = calculateAmbient(intensity, closest_sphere->getAmbient());

	        r += rgbAmbient.x;
	        g += rgbAmbient.y;
	        b += rgbAmbient.z;
		} else{
			//else do shading
			glm::vec3 rgbDiffusion = calculateDiffusion(normal, incident, intensity, closest_sphere->getDiffuse());

	        glm::vec3 rgbSpecular = calculateSpecular(normal, incident, intensity, closest_sphere->getSpecular(), closest_sphere->getSpecularPow(), cam_ray);
	        // glm::vec3 rgbSpecular = calculateSpecular(normal, incident, intensity, closest_sphere, cam_ray);

	        glm::vec3 rgbAmbient = calculateAmbient(intensity, closest_sphere->getAmbient());

	        r += rgbDiffusion.x + rgbSpecular.x + rgbAmbient.x;
	        g += rgbDiffusion.y + rgbSpecular.y + rgbAmbient.y;
	        b += rgbDiffusion.z + rgbSpecular.z + rgbAmbient.z;
		}
	}
	
	for(int num_pl = 0; num_pl < pnt_lights.size(); num_pl++){
		glm::vec3 incident = (pnt_lights[num_pl])->getLightVec(point);
		glm::vec3 intensity = (pnt_lights[num_pl])->getColor();

		//find shadows, skip iteration
		Ray* dir_ray = new Ray(point, incident);
		bool isShadowed = false;

		for(int i = 0; i < spheres.size(); i++){
			Sphere* sphere = spheres[i];

			float t = sphere->intersect(dir_ray);

			if(t > 0.0f || closest_sphere == sphere){
				// delete dir_ray;
				isShadowed = true;
				continue;
			}
		}

		// delete dir_ray;

		if(isShadowed){
	        glm::vec3 rgbAmbient = calculateAmbient(intensity, closest_sphere->getAmbient());

	        r += rgbAmbient.x;
	        g += rgbAmbient.y;
	        b += rgbAmbient.z;
		} else{
			//else do shading
			glm::vec3 rgbDiffusion = calculateDiffusion(normal, incident, intensity, closest_sphere->getDiffuse());

	        glm::vec3 rgbSpecular = calculateSpecular(normal, incident, intensity, closest_sphere->getSpecular(), closest_sphere->getSpecularPow(), cam_ray);

	        glm::vec3 rgbAmbient = calculateAmbient(intensity, closest_sphere->getAmbient());

	        r += rgbDiffusion.x + rgbSpecular.x + rgbAmbient.x;
	        g += rgbDiffusion.y + rgbSpecular.y + rgbAmbient.y;
	        b += rgbDiffusion.z + rgbSpecular.z + rgbAmbient.z;
		}
	}

	r = std::min(1.0f, r);
	g = std::min(1.0f, g);
	b = std::min(1.0f, b);

	// return glm::vec3(r, g, b);

	// reflection recursion
	if(current_depth < max_depth){
		glm::vec3 inc_ray_dir = cam_ray->getDirection();
		glm::vec3 refl_dir = inc_ray_dir - 2 * glm::dot(inc_ray_dir, normal) * normal;
		Ray* refl_ray = new Ray(point, refl_dir);

		glm::vec3 refl_color = traceRecursion(refl_ray, spheres, dir_lights, pnt_lights, max_depth, current_depth + 1);

		glm::vec3 kr = closest_sphere->getReflect();

		float refl_r = std::min(1.0f, r + refl_color.x * kr.x);
		float refl_g = std::min(1.0f, g + refl_color.y * kr.y);
		float refl_b = std::min(1.0f, b + refl_color.z * kr.z);

		return glm::vec3(refl_r, refl_g, refl_b);
	} else{
		return glm::vec3(r, g, b);
	}
}

Color* RayTracer::trace(Ray* cam_ray, std::vector<Sphere*>& spheres, std::vector<DirectionalLight*>& dir_lights, std::vector<PointLight*>& pnt_lights, int max_depth){
	int current_depth = 0;

	glm::vec3 pixelRGB = traceRecursion(cam_ray, spheres, dir_lights, pnt_lights, max_depth, current_depth);

	return new Color(pixelRGB);
}

glm::vec3 RayTracer::calculateDiffusion(glm::vec3 normal, glm::vec3 incident, glm::vec3 intensity, glm::vec3 kd){
	float dot = glm::dot(normal, incident);

	float r = std::max(kd.x * intensity.x * dot, 0.0f);
	float g = std::max(kd.y * intensity.y * dot, 0.0f);
	float b = std::max(kd.z * intensity.z * dot, 0.0f);

	return glm::vec3(r, g, b);
}

glm::vec3 RayTracer::calculateSpecular(glm::vec3 normal, glm::vec3 incident, glm::vec3 intensity, glm::vec3 ks, int sp, Ray* view_ray){
	//reflected
	glm::vec3 r_vec = glm::normalize((-1.0f * incident) + (2.0f * glm::dot(incident, normal) * normal));
	float dot_pow = pow(std::max(0.0f, glm::dot(r_vec, view_ray->getReverseDirection())), sp);

	//half-angle
	// glm::vec3 h_vec = glm::normalize(incident + view_ray->getReverseDirection());
 	// float dot_pow = pow(std::max(0.0f, glm::dot(normal, h_vec)), (int) shading_attr["pow_specular"].x);

	float r = std::max(ks.x * intensity.x * dot_pow, 0.0f);
	float g = std::max(ks.y * intensity.y * dot_pow, 0.0f);
	float b = std::max(ks.z * intensity.z * dot_pow, 0.0f);

	return glm::vec3(r, g, b);
}

glm::vec3 RayTracer::calculateSpecular(glm::vec3 normal, glm::vec3 incident, glm::vec3 intensity, Sphere* sph, Ray* view_ray){
	glm::vec3 ks = sph->getSpecular();
	int sp = sph->getSpecularPow();

	//reflected
	glm::vec3 r_vec = glm::normalize((-1.0f * incident) + (2.0f * glm::dot(incident, normal) * normal));
	glm::mat4 t_mat = sph->getTransform();
	glm::vec4 vr = glm::vec4(view_ray->getDirection(), 0.0f);
	glm::vec3 vr_trans = (t_mat * vr).xyz();
	glm::vec3 neg_vr_trans = -1.0f * vr_trans;
	float dot_pow = pow(std::max(0.0f, glm::dot(r_vec, neg_vr_trans)), sp);

	//half-angle
	// glm::vec3 h_vec = glm::normalize(incident + view_ray->getReverseDirection());
 	// float dot_pow = pow(std::max(0.0f, glm::dot(normal, h_vec)), (int) shading_attr["pow_specular"].x);

	float r = std::max(ks.x * intensity.x * dot_pow, 0.0f);
	float g = std::max(ks.y * intensity.y * dot_pow, 0.0f);
	float b = std::max(ks.z * intensity.z * dot_pow, 0.0f);

	return glm::vec3(r, g, b);
}

glm::vec3 RayTracer::calculateAmbient(glm::vec3 intensity, glm::vec3 ka){
	float r = std::max(ka.x * intensity.x , 0.0f);
	float g = std::max(ka.y * intensity.y, 0.0f);
	float b = std::max(ka.z * intensity.z, 0.0f);

	return glm::vec3(r, g, b);
}

void RayTracer::print(){
	printf("The Ray Tracer");
}