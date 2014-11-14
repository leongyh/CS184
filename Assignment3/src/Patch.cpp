#include "Patch.h"
#include <cstdio>

Patch::Patch(){
	this->curves.reserve(4);
}

Patch::Patch(const Patch& obj){
	this->curves = obj.curves;
}

Patch::~Patch(){

}
		
bool Patch::insertCurve(Curve& c){
	if(this->curves.size() < 4){
		this->curves.push_back(&c);

		return true;
	}else{
		return false;
	}
}
		
std::vector<Curve*> Patch::getDemCurves(){
	return this->curves;
}

void Patch::print(){
	for(int i = 0; i < this->curves.size(); i++){
		printf("Curve #%d:\n", i);
		this->curves[i]->print();
	}
}