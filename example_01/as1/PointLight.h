#include <glm/glm.hpp>

class PointLight{
	glm::vec3 position;
	glm::vec3 color;
	
	public:
		PointLight(float x, float y, float z, float r, float g, float b);
		virtual ~PointLight(); 
		
		void setPosition(float x, float y, float z);
		void setColor(float r, float g, float b);
		
		glm::vec3 getPosition();
		glm::vec3 getColor();
		
		void print();
];