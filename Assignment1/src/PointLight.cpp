#include "PointLight.h"	
#include <cstdlib>
#include <ctime>
#include <cstdio>


PointLight::PointLight(float x, float y, float z, float centerX, float centerY, float centerZ, float scale, float r, float g, float b){
	position = glm::vec3(x * scale + centerX, y * scale + centerY, z * scale + centerZ);
	color = glm::vec3(r, g, b);
}

PointLight::~PointLight(){

}

void PointLight::setPosition(float x, float y, float z){
	position = glm::vec3(x, y, z);
}

void PointLight::setColor(float r, float g, float b){
	color = glm::vec3(r, g, b);
}

glm::vec3 PointLight::getPosition(){
	return position;
}

glm::vec3 PointLight::getColor(){
	return color;
}

glm::vec3 PointLight::getLightVec(float surfaceX, float surfaceY, float surfaceZ){
	glm::vec3 surfaceVec = glm::vec3(surfaceX, surfaceY, surfaceZ);

	return -1.0f * glm::normalize(surfaceVec - position);
}

void PointLight::print(){
	printf("The PointLight coordinates are (%f,%f,%f) of color (%f,%f,%f)", position.x, position.y, position.z, color.x, color.y, color.z);
}