#ifndef SCENE_H_
#define SCENE_H_

#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <string>
#include <utility>

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

#include "ControlPoint.h"
#include "Curve.h"
#include "Patch.h"

class Scene{
	int type;
	float step;
	bool isAdaptive;

	std::vector<Patch*> patches;
	std::vector<ControlPoint*> generated_pts;
	std::vector<glm::vec3> generated_normals;
	public:
		Scene(int type, float u, bool adaptive);
		virtual ~Scene();
		void insertPatch(Patch& patch);
		void render();
		void draw(bool isWire, bool isFlat);
		void print();

	private:
		void uniformSubdivide();
		void adaptiveSubdivide();
		void subdivideTriangle(Patch& patch, ControlPoint& p1, float u1, float v1, ControlPoint& p2, float u2, float v2, ControlPoint& p3, float u3, float v3);
		std::pair<ControlPoint*, glm::vec3> interpolateCurve(Curve& c, float u);
		std::pair<ControlPoint*, glm::vec3> interpolatePatch(Patch& p, float u, float v);
};

#endif