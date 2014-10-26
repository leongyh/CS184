#include "Scene.h"
#include <cstdlib>
#include <cstdio>

Scene::Scene(){
	//dimension for testing purposes. put as constructor params later
	int width = 200;
	int height = 200;

	camera = new Camera(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f);
	sampler = new Sampler(width, height, -1.0f, 1.0f, 1.0f, -1.0f);
	tracer = new RayTracer();
	image = new Film(width, height, "/home/h/test.png");

	//test scene
	shading_attr["k_ambient"] = glm::vec3(0.0f, 0.0f, 0.0f);
	shading_attr["k_specular"] = glm::vec3(1.0f, 1.0f, 1.0f);
	shading_attr["k_diffuse"] = glm::vec3(0.0f, 0.0f, 0.0f);
	shading_attr["pow_specular"] = glm::vec3(20.0f, 0.0f, 0.0f);

	Sphere* s = new Sphere(0.0f, 0.0f, -0.5f, 1.0f);

	spheres.reserve(1);
	spheres.push_back(*s);

	// 200 200 200 0.4 0.8 1.0 -kd 0.7 0.4 0.5
	// -pl 200 200 200 0.4 0.8 1.0 -kd 0.7 0.4 0.5 -ks 1.0 1.0 1.0 -sp 20
	// -pl 200 200 200 0.8 0.8 0.8 -ks 1.0 1.0 1.0 -sp 20 

	// DirectionalLight* dl = new DirectionalLight(-0.5f, -0.3f, -0.9f, 0.8f, 0.8f, 0.8f);
	// dir_lights.reserve(1);
	// dir_lights.push_back(*dl);

	PointLight* pl = new PointLight(0.0f, 0.0f, 200.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.8f, 0.8f, 0.8f);
	pnt_lights.reserve(1);
	pnt_lights.push_back(*pl);
}

Scene::~Scene(){

}

void Scene::defineCamera(Camera* cam){
	camera = cam;
}

void Scene::insertDirectionalLight(DirectionalLight* dl){
	dir_lights.push_back(*dl);
}

void Scene::insertPointLight(PointLight* pl){
	pnt_lights.push_back(*pl);
}

void Scene::insertSphere(Sphere* sphere){
	spheres.push_back(*sphere);
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