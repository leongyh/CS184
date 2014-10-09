#include <glm/glm.hpp>

class MyVector{
	glm::vec3 coordinates;
	
	public:
		MyVector(float x, float y, float z);
		virtual ~MyVector(); 
		
		void setDirection(float x, float y, float z);
		float dotProduct(glm::vec3 vector);

		glm::vec3 getCoordinates();
		
		void print();
};