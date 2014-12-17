#ifndef JOINT_H_
#define JOINT_H_

#include <glm/glm.hpp>

class Joint{
	protected:
		glm::vec3 position;
	
	public:
		Joint(float x, float y, float z);
		Joint(const Joint& obj);
		virtual ~BallJoint(); 
		
		void print();
};

#endif