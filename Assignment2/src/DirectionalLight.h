#ifndef DIRECTIONAL_LIGHT_H_
#define DIRECTIONAL_LIGHT_H_

#include <glm/glm.hpp>

class DirectionalLight{
	glm::vec3 direction;
	glm::vec3 color;
	
	public:
		DirectionalLight(float x, float y, float z, float r, float g, float b);
		DirectionalLight(const DirectionalLight& obj);
		virtual ~DirectionalLight(); 
		
		void setDirection(float x, float y, float z);
		void setColor(float r, float g, float b);
		
		glm::vec3 getDirection();
		glm::vec3 getReverseDirection();
		glm::vec3 getColor();
		
		void print();
};

#endif