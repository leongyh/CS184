#ifndef BALL_JOINT_H_
#define BALL_JOINT_H_

#include <glm/glm.hpp>

class BallJoint{
	glm::vec3 position;
	
	public:
		BallJoint(float x, float y, float z);
		BallJoint(const BallJoint& obj);
		virtual ~BallJoint(); 
		
		void print();
};

#endif