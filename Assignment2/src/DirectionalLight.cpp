#include "DirectionalLight.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>


DirectionalLight::DirectionalLight(float x, float y, float z, float r, float g, float b){
	direction = glm::normalize(glm::vec3(x, y, z));
	color = glm::vec3(r, g, b);
}

DirectionalLight::~DirectionalLight(){

}

void DirectionalLight::setDirection(float x, float y, float z){
	direction = glm::vec3(x, y, z);
}

void DirectionalLight::setColor(float r, float g, float b){
	color = glm::vec3(r, g, b);
}

glm::vec3 DirectionalLight::getDirection(){
	return direction;
}

glm::vec3 DirectionalLight::getReverseDirection(){
	return -1.0f * direction;
}

glm::vec3 DirectionalLight::getColor(){
	return color;
}

void DirectionalLight::print(){
	printf("The DirectionalLight coordinates are (%f,%f,%f) of color (%f,%f,%f)", direction.x, direction.y, direction.z, color.x, color.y, color.z);
}