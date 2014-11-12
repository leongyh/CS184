#include "Curve.h"
#include <stdio>

Curve::Curve(int d){
	this.degree = d;
	this.points.reserve(d+1);
}

Curve::Curve(const Curve& obj){
	this.degree = obj.degree;
	this.points = obj.points;
}

Curve::~Curve(){

}
		
bool Curve::insertPoint(ControlPoint& p){
	if(points.length() < this.degree+1){
		this.points.push_back(p);

		return true;
	}else{
		return false;
	}
}
		
std::vector Curve::getPoints(){
	return this.points;
}

void Curve::print(){

}