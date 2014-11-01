#include "AmbientLight.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>


AmbientLight::AmbientLight(float r, float g, float b){
	color = glm::vec3(r, g, b);
}

AmbientLight::AmbientLight(const AmbientLight& obj){
	color = obj.color;
}

AmbientLight::~AmbientLight(){

}
void AmbientLight::setColor(float r, float g, float b){
	color = glm::vec3(r, g, b);
}


glm::vec3 AmbientLight::getColor(){
	return color;
}

void AmbientLight::print(){
	printf("The AmbientLight is of color (%f,%f,%f)", color.x, color.y, color.z);
}