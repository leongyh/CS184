#include "Goal.h"
#include <cstdlib>
#include <cstdio>


Goal::Goal(float x, float y, float z){
	this->position = glm::vec3(x, y, z);
	displacement = glm::vec3(0.0f, 0.0f, 0.0f);
}

Goal::~Goal(){

}

Goal::Goal(glm::vec3 pos){
	this->position = pos;
}

void Goal::setPosition(float x, float y, float z){
	position = glm::vec3(x, y, z);
}

void Goal::move(float x, float y, float z){
	this->displacement = glm::vec3(x, y, z);
}

glm::vec3 Goal::getPosition(){
	return this->position + displacement;
}

void Goal::draw(){
	glPushMatrix();
		glTranslatef(position.x + displacement.x, position.y + displacement.y, position.z + displacement.z);
		glutSolidSphere(0.1f, 20, 20);
	glPopMatrix();

}

void Goal::print(){
	printf("The Goal position is (%f, %f, %f).\n", position.x + displacement.x, position.y + displacement.y, position.z + displacement.z);
}