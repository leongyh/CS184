#include "PointLight.h"
#include <cstdlib>
#include <ctime>


PointLight::PointLight(float x, float y, float z, float r, float g, float b){
	position = glm::vec3(x, y, z);
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

void PointLight::print(){
	printf("The PointLight coordinates are (%f,%f,%f) of color (%f,%f,%f)", position.x, position.y, position.z, color.x, color.y, color.z); 
}
