#ifndef LIGAMENT_H_
#define LIGAMENT_H_

#include <glm/glm.hpp>
#include "Joint.h"

class Ligament{
	Joint* joint1;
	Joint* joint2;
	
	public:
		Ligament(Joint& j1, Joint& j2);
		Ligament(const Ligament& obj);
		virtual ~Ligament();

		void draw();
		
		void print();
};

#endif