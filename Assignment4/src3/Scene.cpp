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
	
}

void Scene::draw(){
	glutSolidCone(1.0, 1.0, 50, 50);
}

void Scene::print(){
	printf("The Scene.");
}