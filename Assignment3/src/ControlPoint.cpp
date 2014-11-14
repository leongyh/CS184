#include "ControlPoint.h"
#include <cstdio>

ControlPoint::ControlPoint(float x, float y, float z){
	this->position = glm::vec3(x, y, z);
}

ControlPoint::ControlPoint(glm::vec3 pos){
	this->position = pos;
}

ControlPoint::ControlPoint(const ControlPoint& obj){
	this->position = obj.position;
}

ControlPoint::~ControlPoint(){

}

void ControlPoint::setPosition(float x, float y, float z){
	this->position = glm::vec3(x, y, z);
}


glm::vec3 ControlPoint::getPosition(){
	return this->position;
}

void ControlPoint::print(){
	printf("The ControlPoint coordinates are (%f,%f,%f).\n", this->position.x, this->position.y, this->position.z);
}