#include "Scene.h"
#include <cstdlib>
#include <cstdio>

Scene::Scene(){
	//dimension for testing purposes. put as constructor params later
	int width = 200;
	int height = 100;

	camera = new Camera(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	sampler = new Sampler(width, height, -1.0f, 1.0f, 1.0f, -1.0f);
	tracer = new RayTracer();
	image = new Film(width, height, "/home/h/test11.png");

	//test scene
	Sphere* s = new Sphere(4.0f, 0.0f, 0.0f, 1.0f);

	spheres.reserve(1);
	spheres.push_back(*s);
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

		Color* c = tracer->trace(r, spheres);
		// c->print();
		
		image->addPixel(s, c);
	}

	image->encode();
}

void Scene::print(){
	printf("The Scene");
}