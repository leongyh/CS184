#ifndef CONTROL_POINT_H_
#define CONTROL_POINT_H_

#include <glm/glm.hpp>

class ControlPoint{
	glm::vec3 position;
	
	public:
		ControlPoint(float x, float y, float z);
		ControlPoint(glm::vec3 pos);
		ControlPoint(const ControlPoint& obj);
		virtual ~ControlPoint(); 
		
		void setPosition(float x, float y, float z);
		
		glm::vec3 getPosition();
		
		void print();
};

#endif