#include "Scene.h"
#include <cstdlib>
#include <cstdio>

Scene::Scene(){
	//dimension for testing purposes. put as constructor params later
	int width = 200;
	int height = 200;

	camera = new Camera(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	sampler = new Sampler(width, height, -1.0f, 1.0f, 1.0f, -1.0f);
	tracer = new RayTracer();
	image = new Film(width, height, "/home/h/test.png");

	//test scene
	shading_attr["k_ambient"] = glm::vec3(0.2f, 0.2f, 0.2f);
	shading_attr["k_specular"] = glm::vec3(0.3f, 0.3f, 0.3f);
	shading_attr["k_diffuse"] = glm::vec3(0.7f, 0.5f, 0.5f);
	shading_attr["pow_specular"] = glm::vec3(8.0f, 0.0f, 0.0f);

	Sphere* s = new Sphere(4.0f, 0.0f, 0.0f, 1.0f);

	spheres.reserve(1);
	spheres.push_back(*s);

	DirectionalLight* dl = new DirectionalLight(1.0f, -0.8f, -1.0f, 1.0f, 0.1f, 0.1f);

	dir_lights.reserve(1);
	dir_lights.push_back(*dl);
}

Scene::~Scene(){

}

void Scene::render(){
	printf("Rendering start...\n");
	// camera->print();	

	while(sampler->hasNext()){
		Sample* s = sampler->sampleNext();
		// s->print();

		Ray* r = camera->emitRay(s);
		// r->print();

		// Color* c = tracer->trace(r, spheres);
		Color* c = tracer->trace(r, spheres, dir_lights, pnt_lights, shading_attr);
		// c->print();
		
		image->addPixel(s, c);
	}

	image->encode();
}

void Scene::print(){
	printf("The Scene");
}