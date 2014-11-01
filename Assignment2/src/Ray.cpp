#include "Ray.h"
#include <cstdlib>
#include <cstdio>


Ray::Ray(float px, float py, float pz, float dx, float dy, float dz){
	position = glm::vec3(px, py, pz);
	direction = glm::vec3(dx, dy, dz);
}

Ray::Ray(glm::vec3 point, glm::vec3 dir){
	position = point;
	direction = dir;
}

Ray::~Ray(){

}


glm::vec3 Ray::getPosition(){
	return position;
}

glm::vec3 Ray::getDirection(){
	return direction;
}

glm::vec3 Ray::getReverseDirection(){
	return -1.0f * direction;
}

glm::vec3 Ray::getPoint(float t){
	return position + t * direction;
}

void Ray::print(){
	printf("The ray origin is (%f,%f,%f) of direction (%f,%f,%f)\n", position.x, position.y, position.z, direction.x, direction.y, direction.z);
}