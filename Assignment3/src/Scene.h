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

	std::vector<DirectionalLight*> dir_lights;
	std::vector<PointLight*> pnt_lights;
	std::vector<Patch*> patches;

	public:
		Scene(int type, float u);
		virtual ~Scene();
		void insertDirectionalLight(DirectionalLight& dl);
		void insertPointLight(PointLight& pl);
		void insertPatch(Patch& patch);
		void render(bool isWire, bool isFlat);

		void print();

	private:
		void uniformSubdivide(bool isWire, bool isFlat);
		std::pair<ControlPoint*, glm::vec3> interpolateCurve(Curve& c, float u);
		std::pair<ControlPoint*, glm::vec3> interpolatePatch(Patch& p, float u, float v);
};

#endif