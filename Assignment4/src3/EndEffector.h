#ifndef END_EFFECTOR_H_
#define END_EFFECTOR_H_

#include <glm/glm.hpp>

#include "Joint.h"

class EndEffector : public Joint{
	glm::vec3 position;
	
	public:
		EndEffector(float x, float y, float z);
		EndEffector(const BallJoint& obj);
		virtual ~EndEffector(); 
		
		void print();
};

#endif