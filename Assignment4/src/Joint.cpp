#include "Joint.h"
#include <cstdio>

Joint::Joint(float x, float y, float z, float l){
	this->angles = glm::vec3(x, y, z);
	this->length = l;
}

Joint::Joint(const Joint& obj){
	this->angles = obj.angles;
	this->length = obj.length;
}

Joint::~Joint(){

}

void Joint::updateAngles(float x, float y, float z){
	this->angles = this->angles + glm::vec3(x, y, z);
}

// void Joint::rotateQuarternion(float x, float y, float z){
// 	Quaternion q, work, qp(*this);
// 	work.LoadIdentity();

// 	if(x){
// 		q.SetRotation(x, 0, 0);
// 		work *= q;
// 	}

// 	if(y){
// 		q.SetRotation(0, y, 0);
// 		work *= q;
// 	}

// 	if(z){
// 		q.SetRotation(0, 0, z);
// 		work *= q;
// 	}

// 	Quaternion calc;
// 	calc = (work*qp);
// 	calc *= work.Conjugate();

// 	this->angles = glm::vec3((float)calc.x, (float)calc.y, (float)calc.z);
// }

float Joint::getAngle(){
	return glm::length(this->angles);
}

glm::vec3 Joint::getAngles(){
	this->angles;
}

glm::vec3 Joint::getAxis(){
	return glm::normalize(this->angles);
}

float Joint::getLength(){
	return this->length;
}

void Joint::print(){
	printf("The Joint angles are (%f,%f,%f) and length %f.\n", this->angles.x, this->angles.y, this->angles.z, this->length);
}