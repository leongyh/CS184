#include <glm/glm.hpp>
#include "Camera.h"
#include "Sampler.h"
#include "RayTracer.h"
#include "Film.h"
#include "Sample.h"
#include "Sphere.h"
#include "DirectionalLight"

class Scene{
	Camera camera;
	Sampler sampler;
	RayTracer tracer;
	Film image;

	std::vector<Sphere> spheres;
	std::vector<DirectionalLight> d_lights;

	public:
		Scene();
		virtual ~Scene();

		void render();

		void print();
};