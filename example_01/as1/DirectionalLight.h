#include <glm/glm.hpp>

class DirectionalLight{
	glm::vec3 direction;
	glm::vec3 color;
	
	public:
		DirectionalLight(float x, float y, float z, float r, float g, float b);
		virtual ~DirectionalLight(); 
		
		void setDirection(float x, float y, float z);
		void setColor(float r, float g, float b);
		
		glm::vec3 getDirection();
		glm::vec3 getColor();
		
		void print();
];