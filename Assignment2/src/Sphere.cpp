#include "Sphere.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>

Sphere::Sphere(float x, float y, float z, float r){
	position = glm::vec3(x, y, z);
	radius = r;
}

Sphere::Sphere(const Sphere& obj){
	position = obj.position;
	// *obj.position = glm::vec3(position.x, position.y, position.z);
	radius = obj.radius;
}

Sphere::~Sphere(){

}

glm::vec3 Sphere::getNormal(glm::vec3 point){
	return (point - position) / radius;
}

float Sphere::intersect(Ray* cam_ray){
	glm::vec3 ray_dir = cam_ray->getDirection();
	glm::vec3 ray_pos = cam_ray->getPosition();

	float descriminant = sqrt(pow(glm::dot(ray_dir, (ray_pos - position)), 2) - glm::dot(ray_dir, ray_dir) * (glm::dot(ray_pos - position, ray_pos - position) - pow(radius, 2)));

	if(descriminant < 0 ){
		return -1.0f;  //no solution
	} else if(descriminant == 0){
		float t = glm::dot(-1.0f * ray_dir, ray_pos - position) / glm::dot(ray_dir, ray_dir);

		return t;
	} else{
		float t_plus = (glm::dot(-1.0f * ray_dir, ray_pos - position) + descriminant) / glm::dot(ray_dir, ray_dir);
		float t_minus = (glm::dot(-1.0f * ray_dir, ray_pos - position) - descriminant) / glm::dot(ray_dir, ray_dir);

		return std::min(t_plus, t_minus);
	}
}

void Sphere::print(){
	printf("The Sphere coordinates are (%f,%f,%f) with radius %f", position.x, position.y, position.z, radius);
}