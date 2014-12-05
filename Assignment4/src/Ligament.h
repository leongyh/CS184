#ifndef LIGAMENT_H_
#define LIGAMENT_H_

#include <glm/glm.hpp>
#include "BallJoint.h"

class Ligament{
	BallJoint* bj1;
	BallJoint* bj2;
	
	public:
		Ligament(BallJoint& j1, BallJoint& j2);
		Ligament(const Ligament& obj);
		virtual ~Ligament();

		void draw();
		
		void print();
};

#endif