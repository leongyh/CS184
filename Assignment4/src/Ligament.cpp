#include "Ligament.h"
#include <cstdio>

Ligament::Ligament(Joint& j1, Joint& j2){
	this->joint1 = j1;
	this->joint2 = j2;
}

Ligament::Ligament(const Ligament& obj){
	this->joint1 = obj.joint1;
	this->joint2 = obj.joint2;
}

Ligament::~Ligament(){

}

Ligament::draw(){
	
}

void Ligament::print(){
	printf("The Ligament has Joints of coordinates:\n");
}