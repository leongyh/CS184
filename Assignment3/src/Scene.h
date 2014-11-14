#ifndef SCENE_H_
#define SCENE_H_

#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include "ControlPoint.h"
#include "Curve.h"
#include "Patch.h"
#include "DirectionalLight.h"
#include "PointLight.h"

class Scene{
	float step;

	std::vector<DirectionalLight*> dir_lights;
	std::vector<PointLight*> pnt_lights;
	std::vector<Patch*> patches;

	public:
		Scene(float u);
		virtual ~Scene();
		void insertDirectionalLight(DirectionalLight& dl);
		void insertPointLight(PointLight& pl);
		void insertPatch(Patch& patch);
		void render();

		void print();

	private:
		void uniformSubdivide();
		std::pair<ControlPoint*, glm::vec3> interpolateCurve(Curve& c, float u);
		std::pair<ControlPoint*, glm::vec3> interpolatePatch(Patch& p, float u, float v);
};

#endif