#include "Ray.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>


Ray::Ray(float px, float py, float pz, float dx, float dy, float dz, float r, float, float b){
	position = glm::vec3(px, py, pz);
	direction = glm::vec3(dx, dy, dz);
	color = glm::vec3(r, g, b);
}

glm::vec3 Ray::getPosition(){
	return position;
}

glm::vec3 Ray::getDirection(){
	return direction;
}

void Ray::print(){
	printf("The ray coordinates are (%f,%f,%f) of direction (%f,%f,%f)", position., position.y, position.z, direction.x, direction.y, direction.z);
}