#include "Scene.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>


Scene::Scene(float ULx, float ULy, float ULz, float LLx, float LLy, float LLz, float URx, float URy, float URz, float LRx, float LRy, float LRz, Camera cam){
	UL = glm::vec3(ULx, ULy, ULz);
	LL = glm::vec3(LLx, LLy, LLz);
	UR = glm::vec3(URx, URy, URz);
	LR = glm::vec3(LRx, LRy, LRz);
	
	cam = cam;
	rays = new std::vector<Ray>();
}

Scene::~Scene(){

}

void Scene::render(){

}

void Scene::print(){
	printf("The Scene coordinates [UL, LL, UR, RR] are [(%f,%f,%f), (%f,%f,%f), (%f,%f,%f), (%f,%f,%f)]", UL.x, UL.y, UL.z, LL.x, LL.y, LL.z, UR.x, UR.y, UR.z, LR.x, LR.y, LR.z);
}