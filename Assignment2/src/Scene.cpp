#include "Scene.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>


Scene::Scene(){
	camera = new Camera(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	sampler = new Sampler(100, 100, -1.0f, 1.0f, 1.0f, -1.0f);
	tracer = new RayTracer();
	image = new Film(100, 100, "../img/test.png");

	spheres = new std::vector<Sphere>();
	spheres.add(new Sphere(4.0f, 0.0f, 0.0f, 1.0f));
}

Scene::~Scene(){

}

void Scene::render(){
	while(!sampler.hasNext()){
		Sample s = sampler.sampleNext();
		Ray r = camera.emitRay(s);
		Color c = tracer.trace(r, spheres);

		image.addPixel(s, c);
	}

	image.encode();
}

void Scene::print(){
	printf("The Scene");
}