#include "Patch.h"
#include <stdio>

Patch::Patch(){
	this.curves.reserve(4);
}

Patch::Patch(const Patch& obj){
	this.curves = obj.curves;
}

Patch::~Patch(){

}
		
bool Patch::insertCurve(Curve& c){
	if(points.length() < 4){
		this.curves.push_back(c);

		return true;
	}else{
		return false;
	}
}
		
std::vector Patch::getDemCurves(){
	return this.curves;
}

void Patch::print(){

}