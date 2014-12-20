#include "Scene.h"
#include <cstdlib>
#include <cstdio>


Scene::Scene(){
	this->path = NULL;
	this->arm = new Arm();
	this->goal = arm->generateGoal();
	this->step = 0.0;
	this->solver = new IKSolver();
}

Scene::Scene(Path* p){
	this->path = p;
	this->arm = new Arm();
	this->goal = arm->generateGoal();
	this->step = 0.0;
	this->solver = new IKSolver();

	glm::vec3 pos = path->getPosition(0.0f);
	goal->setPosition(pos);

	solver->hardSolve(*arm, *goal);
}

Scene::~Scene(){

}


void Scene::render(float x, float y, float z){
	// printf("Rendering start...\n");
	goal->move(x, y, z);
	solver->solve(*arm, *goal);
}

void Scene::renderPath(){
	glm::vec3 p = path->getPosition(step);
	goal->setPosition(p);
	solver->solve(*arm, *goal);

	step += 0.25;
}

void Scene::drawArm(){
	this->arm->draw();
}

void Scene::drawGoal(){
	this->goal->draw();
}

void Scene::drawPath(){
	this->path->draw();
}

void Scene::print(){
	printf("The Scene.");
}