#ifndef POINT_LIGHT_H_
#define POINT_LIGHT_H_

#include <glm/glm.hpp>

class PointLight{
	glm::vec3 position;
	glm::vec3 color;
	int falloff;
	
	public:
		PointLight(float x, float y, float z, float r, float g, float b);
		PointLight(float x, float y, float z, float r, float g, float b, int f);
		PointLight(const PointLight& obj);
		virtual ~PointLight(); 
		
		void setPosition(float x, float y, float z);
		void setColor(float r, float g, float b);
		
		glm::vec3 getPosition();
		glm::vec3 getColor(glm::vec3 point);
		glm::vec3 getLightVec(glm::vec3 point);
		
		void print();
};

#endif