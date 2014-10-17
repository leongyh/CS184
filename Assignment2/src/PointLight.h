#ifndef POINT_LIGHT_H_
#define POINT_LIGHT_H_

#include <glm/glm.hpp>

class PointLight{
	glm::vec3 position;
	glm::vec3 color;
	
	public:
		PointLight(float x, float y, float z, float centerX, float centerY, float centerZ, float scale, float r, float g, float b);
		PointLight(const PointLight& obj);
		virtual ~PointLight(); 
		
		void setPosition(float x, float y, float z);
		void setColor(float r, float g, float b);
		
		glm::vec3 getPosition();
		glm::vec3 getColor();
		glm::vec3 getLightVec(glm::vec3 point);
		
		void print();
};

#endif