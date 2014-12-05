#include "Scene.h"
#include <cstdlib>
#include <cstdio>

Scene::Scene(){
	this->type = 0;
	this->step = u;
	this->isAdaptive = adaptive;
}

Scene::~Scene(){

}

void Scene::render(){
	// printf("Rendering start...\n");
	if(this->isAdaptive){
		adaptiveSubdivide();
	} else{
		uniformSubdivide();
	}
}

void Scene::draw(){

}

void Scene::print(){
	printf("The Scene.");
}