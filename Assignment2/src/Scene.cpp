#include "Scene.h"
#include <cstdlib>
#include <cstdio>

Scene::Scene(){
	tracer = new RayTracer();
	recursion_depth = 5;
}

Scene::Scene(int depth){
	tracer = new RayTracer();
	recursion_depth = depth;
}

Scene::~Scene(){

}

void Scene::defineCamera(Camera* cam){
	camera = cam;
}

void Scene::defineImage(int w, int h, const std::string file_loc){
	sampler = new Sampler(w, h, 0.0f, 1.0f, 1.0f, 0.0f);
	image = new Film(w, h, file_loc);
}

void Scene::insertAmbientLight(AmbientLight* al){
	amb_lights.push_back(al);
}

void Scene::insertDirectionalLight(DirectionalLight* dl){
	dir_lights.push_back(dl);
}

void Scene::insertPointLight(PointLight* pl){
	pnt_lights.push_back(pl);
}

void Scene::insertSphere(Sphere* sphere){
	spheres.push_back(sphere);
}

void Scene::insertTriangle(Triangle* tri){
	triangles.push_back(tri);
}

void Scene::render(){
	printf("Rendering start...\n");
	// camera->print();
	// sampler->print();
	// image->print();

	while(sampler->hasNext()){
		Sample* s = sampler->sampleNext();
		// s->print();

		Ray* r = camera->emitRay(s);
		// r->print();

		// Color* c = tracer->trace(r, spheres);
		Color* c = tracer->trace(r, spheres, triangles, amb_lights, dir_lights, pnt_lights, recursion_depth);
		// c->print();
		
		image->addPixel(s, c);
	}

	image->encode();
}

void Scene::print(){
	printf("The Scene");
}