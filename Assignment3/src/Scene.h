#ifndef SCENE_H_
#define SCENE_H_

#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <string>
#include "Patch.h"
#include "DirectionalLight.h"
#include "PointLight.h"

class Scene{
	// std::vector<AmbientLight*> amb_lights;
	std::vector<DirectionalLight*> dir_lights;
	std::vector<PointLight*> pnt_lights;
	std::vector<Patch*> patches;

	public:
		Scene();
		virtual ~Scene();
		void insertDirectionalLight(DirectionalLight& dl);
		void insertPointLight(PointLight& pl);
		void insertPatch(Patch& patch);
		void render();

		void print();
};

#endif