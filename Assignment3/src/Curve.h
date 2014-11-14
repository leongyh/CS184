#ifndef CURVE_H_
#define CURVE_H_

#include <glm/glm.hpp>
#include <vector>

#include "ControlPoint.h"

class Curve{
	int degree;
	std::vector<ControlPoint*> points;
	
	public:
		Curve(int d);
		Curve(const Curve& obj);
		virtual ~Curve(); 
		
		bool insertPoint(ControlPoint& p);
		
		std::vector<ControlPoint*> getPoints();
		
		void print();
};

#endif