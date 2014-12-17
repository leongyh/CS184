#ifndef ARM_H_
#define ARM_H_

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

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

#include "Joint.h"

class Arm{
	std::vector<Joint*> joints;
	// Joint* base;
	Joint* end;
	
	public:
		Arm();
		Arm(const Arm& obj);
		virtual ~Arm();

		void applyDeltaAngle(std::vector<float>& dA);
		glm::vec3 getEndPoint();
		glm::vec3 getJointPos(int i);
		std::vector<Joint*> getJoints();
		void draw();
		
		void print();
};

#endif