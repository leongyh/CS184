#include "Scene.h"
#include <cstdlib>
#include <cstdio>

Scene::Scene(){
	
}

Scene::~Scene(){

}

void Scene::insertDirectionalLight(DirectionalLight& dl){
	this.dir_lights.push_back(dl);
}

void Scene::insertPointLight(PointLight& pl){
	this.pnt_lights.push_back(pl);
}

void Scene::insertPatch(Patch& patch){
	this.patches.push_back(patch);
}

void Scene::render(){
	printf("Rendering start...\n");
	
}

void Scene::print(){
	printf("The Scene");
}