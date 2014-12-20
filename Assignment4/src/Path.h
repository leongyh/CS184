#ifndef PATH_H_
#define PATH_H_

#define PI 3.14159265

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

#include <math.h>

class Path{
	int type;

	public:
		Path(int n);
		virtual ~Path(); 

		glm::vec3 getPosition(float t);
		void draw();
		
		void print();
};

#endif