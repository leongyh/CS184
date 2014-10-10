#include "Sphere.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>


Sphere::Sphere(float x, float y, float z, float r){
	position = glm::vec3(x, y, z);
	radius = r
}

Sphere::~Sphere(){

}

void Sphere::print(){
	printf("The Sphere coordinates are (%f,%f,%f) with radius %f", position.x, position.y, position.z, radius);
}