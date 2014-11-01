#ifndef AMBIENT_LIGHT_H_
#define AMBIENT_LIGHT_H_

#include <glm/glm.hpp>

class AmbientLight{
	glm::vec3 direction;
	glm::vec3 color;
	
	public:
		AmbientLight(float r, float g, float b);
		AmbientLight(const AmbientLight& obj);
		virtual ~AmbientLight();

		void setColor(float r, float g, float b);
		glm::vec3 getColor();

		void print();
};

#endif