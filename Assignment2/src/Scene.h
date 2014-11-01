#ifndef SCENE_H_
#define SCENE_H_

#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <string>
#include "Camera.h"
#include "Sampler.h"
#include "RayTracer.h"
#include "Film.h"
#include "Sphere.h"
#include "Triangle.h"
#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"

class Scene{
	Camera* camera;
	Sampler* sampler;
	RayTracer* tracer;
	Film* image;

	std::vector<AmbientLight*> amb_lights;
	std::vector<DirectionalLight*> dir_lights;
	std::vector<PointLight*> pnt_lights;
	std::vector<Sphere*> spheres;
	std::vector<Triangle*> triangles;

	int recursion_depth;

	public:
		Scene();
		Scene(int depth);
		virtual ~Scene();

		void defineCamera(Camera* cam);
		void defineImage(int w, int h, const std::string file_loc);
		void insertAmbientLight(AmbientLight* al);
		void insertDirectionalLight(DirectionalLight* dl);
		void insertPointLight(PointLight* pl);
		void insertSphere(Sphere* sphere);
		void insertTriangle(Triangle* tri);

		void render();

		void print();
};

#endif