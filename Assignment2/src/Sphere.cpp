#include "Sphere.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>

Sphere::Sphere(float x, float y, float z, float r){
	position = glm::vec3(x, y, z);
	radius = r;

	k_ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	k_diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
	k_specular = glm::vec3(0.0f, 0.0f, 0.0f);
	k_reflect = glm::vec3(0.0f, 0.0f, 0.0f);

	specular_pow = 1;
}

Sphere::Sphere(const Sphere& obj){
	position = obj.position;
	radius = obj.radius;
	k_ambient = obj.k_ambient;
	k_diffuse = obj.k_diffuse;
	k_specular = obj.k_specular;
	k_reflect = obj.k_reflect;
	specular_pow = obj.specular_pow;
}

Sphere::~Sphere(){

}

void Sphere::setAmbient(glm::vec3 ka){
	k_ambient = ka;
}

void Sphere::setDiffuse(glm::vec3 kd){
	k_diffuse = kd;
}

void Sphere::setSpecular(glm::vec3 ks){
	k_specular = ks;
}

void Sphere::setSpecularPow(int sp){
	specular_pow = sp;
}

void Sphere::setReflect(glm::vec3 kr){
	k_reflect = kr;
}

glm::vec3 Sphere::getAmbient(){
	return k_ambient;
}

glm::vec3 Sphere::getDiffuse(){
	return k_diffuse;
}

glm::vec3 Sphere::getSpecular(){
	return k_specular;
}

int Sphere::getSpecularPow(){
	return specular_pow;
}

glm::vec3 Sphere::getReflect(){
	return k_reflect;
}

glm::vec3 Sphere::getNormal(glm::vec3 point){
	glm::vec3 normal = (point - position) / radius;

	return normal;
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
	printf("The Sphere coordinates are (%f,%f,%f) with radius %f\n", position.x, position.y, position.z, radius);
}