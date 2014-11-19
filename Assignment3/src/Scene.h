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
#include "DirectionalLight.h"
#include "PointLight.h"

class Scene{
	int type;
	float step;

	std::vector<Patch*> patches;
	std::vector<ControlPoint*> generated_pts;
	std::vector<glm::vec3> generated_normals;

	public:
		Scene(int type, float u);
		virtual ~Scene();
		void insertPatch(Patch& patch);
		void render();
		void draw(bool isWire, bool isFlat);
		void print();

	private:
		void uniformSubdivide();
		std::pair<ControlPoint*, glm::vec3> interpolateCurve(Curve& c, float u);
		std::pair<ControlPoint*, glm::vec3> interpolatePatch(Patch& p, float u, float v);
};

#endif