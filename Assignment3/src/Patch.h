#ifndef PATCH_H_
#define PATCH_H_

#include <glm/glm.hpp>
#include <vector>

#include "Curve.h"

class Patch{
	std::vector<Curve*> curves;
	
	public:
		Patch();
		Patch(const Patch& obj);
		virtual ~Patch(); 
		
		bool insertCurve(Curve& c);
		
		std::vector getDemCurves();
		
		void print();
};

#endif