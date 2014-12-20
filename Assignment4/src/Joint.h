#ifndef JOINT_H_
#define JOINT_H_

#include <glm/glm.hpp>

class Joint{
	glm::vec3 angles;
	float length;
	
	public:
		Joint(float x, float y, float z, float l);
		Joint(const Joint& obj);
		virtual ~Joint();

		void updateAngles(float x, float y, float z);
		float getAngle();
		glm::vec3 getAngles();
		glm::vec3 getAxis();
		float getLength();
		
		void print();
};

#endif