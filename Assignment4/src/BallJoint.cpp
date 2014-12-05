#include "BallJoint.h"
#include <cstdio>

BallJoint::BallJoint(float x, float y, float z){
	this->position = glm::vec3(x, y, z);
}

BallJoint::BallJoint(const BallJoint& obj){
	this->position = obj.position;
}

BallJoint::~BallJoint(){

}

void BallJoint::print(){
	printf("The BallJoint coordinates are (%f,%f,%f).\n", this->position.x, this->position.y, this->position.z);
}