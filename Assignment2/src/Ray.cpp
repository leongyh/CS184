#include "Ray.h"
#include <cstdlib>
#include <cstdio>


Ray::Ray(float px, float py, float pz, float dx, float dy, float dz){
	position = glm::vec3(px, py, pz);
	direction = glm::vec3(dx, dy, dz);
}

Ray::~Ray(){

}


glm::vec3 Ray::getPosition(){
	return position;
}

glm::vec3 Ray::getDirection(){
	return direction;
}

void Ray::print(){
	printf("The ray coordinates are (%f,%f,%f) of direction (%f,%f,%f)", position.x, position.y, position.z, direction.x, direction.y, direction.z);
}