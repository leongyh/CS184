#ifndef SCENE_H_
#define SCENE_H_

#include <glm/glm.hpp>
#include <Eigen/Dense>
#include <vector>
#include <string>

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
#include "Arm.h"
#include "Goal.h"
#include "IKSolver.h"
#include "Path.h"

class Scene{
	Path* path;
	Arm* arm;
	Goal* goal;
	IKSolver* solver;
	float step;

	public:
		Scene();
		Scene(Path* path);
		virtual ~Scene();
		void render(float x, float y, float z);
		void renderPath();
		void drawArm();
		void drawGoal();
		void drawPath();
		void print();
};

#endif