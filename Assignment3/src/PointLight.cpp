#include "PointLight.h"
#include <cstdio>
#include <cmath>

PointLight::PointLight(float x, float y, float z, float r, float g, float b){
	position = glm::vec3(x, y, z);
	color = glm::vec3(r, g, b);
	falloff = 0;
}

PointLight::PointLight(float x, float y, float z, float r, float g, float b, int f){
	position = glm::vec3(x, y, z);
	color = glm::vec3(r, g, b);
	falloff = f;
}

PointLight::PointLight(const PointLight& obj){
	position = obj.position;
	color = obj.color;
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

glm::vec3 PointLight::getColor(glm::vec3 point){
	if(falloff == 0){
		return color;
	} else{
		float length = glm::length(position - point);
		float fall_pow = std::pow(length, falloff);

		return color / fall_pow;
	}
}

glm::vec3 PointLight::getLightVec(glm::vec3 point){
	return glm::normalize(position - point);
}

void PointLight::print(){
	printf("The PointLight coordinates are (%f,%f,%f) of color (%f,%f,%f)", position.x, position.y, position.z, color.x, color.y, color.z);
}