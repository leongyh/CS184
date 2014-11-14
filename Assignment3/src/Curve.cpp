#include "Curve.h"
#include <cstdio>

Curve::Curve(int d){
	this->degree = d;
	this->points.reserve(d+1);
}

Curve::Curve(const Curve& obj){
	this->degree = obj.degree;
	this->points = obj.points;
}

Curve::~Curve(){

}
		
bool Curve::insertPoint(ControlPoint& p){
	if(this->points.size() < this->degree + 1){
		this->points.push_back(&p);

		return true;
	}else{
		return false;
	}
}
		
std::vector<ControlPoint*> Curve::getPoints(){
	return this->points;
}

void Curve::print(){
	for(int i = 0; i < this->points.size(); i++){
		this->points[i]->print();
	}
}