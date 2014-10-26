#include "Triangle.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>

Triangle::Triangle(glm::vec3 z1, glm::vec3 z2, glm::vec3 z3){
	v1 = z1;
	v2 = z2;
	v3 = z3;

	k_ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	k_diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
	k_specular = glm::vec3(0.0f, 0.0f, 0.0f);
	k_reflect = glm::vec3(0.0f, 0.0f, 0.0f);

	specular_pow = 1;
}

Triangle::Triangle(const Triangle& obj){
	v1 = obj.v1;
	v2 = obj.v2;
	v3 = obj.v3;
	k_ambient = obj.k_ambient;
	k_diffuse = obj.k_diffuse;
	k_specular = obj.k_specular;
	k_reflect = obj.k_reflect;
	specular_pow = obj.specular_pow;
}

Triangle::~Triangle(){

}

void Triangle::setAmbient(glm::vec3 ka){
	k_ambient = ka;
}

void Triangle::setDiffuse(glm::vec3 kd){
	k_diffuse = kd;
}

void Triangle::setSpecular(glm::vec3 ks){
	k_specular = ks;
}

void Triangle::setSpecularPow(int sp){
	specular_pow = sp;
}

void Triangle::setReflect(glm::vec3 kr){
	k_reflect = kr;
}

glm::vec3 Triangle::getAmbient(){
	return k_ambient;
}

glm::vec3 Triangle::getDiffuse(){
	return k_diffuse;
}

glm::vec3 Triangle::getSpecular(){
	return k_specular;
}

int Triangle::getSpecularPow(){
	return specular_pow;
}

glm::vec3 Triangle::getReflect(){
	return k_reflect;
}

glm::vec3 Triangle::getNormal(){
	return v1;
}

float Triangle::intersect(Ray* cam_ray){
	return 0.0f;
}

void Triangle::print(){
	printf("The trangle has vectors v1: (%f,%f,%f), v2: (%f,%f,%f), v3: (%f,%f,%f)\n", v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z);
}