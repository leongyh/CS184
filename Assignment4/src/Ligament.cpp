#include "Ligament.h"
#include <cstdio>

Ligament::Ligament(BallJoint& j1, BallJoint& j2){
	this->bj1 = j1;
	this->bj2 = j2;
}

Ligament::Ligament(const Ligament& obj){
	this->bj1 = obj.bj1;
	this->bj2 = obj.bj2;
}

Ligament::~Ligament(){

}

Ligament::draw(){
	
}

void Ligament::print(){
	printf("The Ligament has Joints of coordinates:\n");
}