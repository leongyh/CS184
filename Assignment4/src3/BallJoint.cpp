#include "BallJoint.h"
#include <cstdio>

BallJoint::BallJoint(float x, float y, float z) : Joint(float x, float y, float z){

}

BallJoint::BallJoint(const BallJoint& obj){
	this->position = obj.position;
}

BallJoint::~BallJoint(){

}

void BallJoint::print(){
	printf("The BallJoint coordinates are (%f,%f,%f).\n", this->position.x, this->position.y, this->position.z);
}