#ifndef GOAL_H_
#define GOAL_H_

#include <glm/glm.hpp>

class Goal{
	protected:
		glm::vec3 position;
	
	public:
		Goal(float x, float y, float z);
		Goal(const Goal& obj);
		virtual ~Goal(); 
		
		void print();
};

#endif