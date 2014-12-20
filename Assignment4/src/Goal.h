#ifndef GOAL_H_
#define GOAL_H_

#include <glm/glm.hpp>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

class Goal{
	protected:
		glm::vec3 position;
		glm::vec3 displacement;
	
	public:
		Goal(float x, float y, float z);
		Goal(glm::vec3 pos);
		virtual ~Goal(); 

		void setPosition(float x, float y, float z);
		void setPosition(glm::vec3 p);
		void move(float x, float y, float z);
		glm::vec3 getPosition();
		void draw();
		
		void print();
};

#endif