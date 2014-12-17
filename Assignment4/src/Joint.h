#ifndef JOINT_H_
#define JOINT_H_

#include <glm/glm.hpp>
// #include "Quarternion.h"

class Joint{
	// Joint* parent;
	// glm::vec3 world_position;
	// glm::vec3 local_position;
	glm::vec3 angles;
	float length;
	
	public:
		Joint(float x, float y, float z, float l);
		// Joint(float x, float y, float z, float ax, float ay, float az, float l);
		Joint(const Joint& obj);
		virtual ~Joint();

		void updateAngles(float x, float y, float z);
		// void rotateQuarternion(float x, float y, float z);
		glm::vec3 getAngles();
		float getLength();
		
		void print();
};

#endif