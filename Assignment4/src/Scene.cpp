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

// Scene::initializePath(){
	
// }

void Scene::renderPath(){
	glm::vec3 p = path->getPosition(step);
	goal->setPosition(p);
	solver->solve(*arm, *goal);

	step += 0.25;
}

void Scene::drawArm(){
	this->arm->draw();
	// goal->print();

	// glm::vec3 p = this->arm->getEndPoint();
	// glm::vec3 p = this->arm->getJointPos(3);

	// glPushMatrix();
	// 	glTranslatef(p.x, p.y, p.z);
	// 	glutSolidSphere(0.5f, 20, 20);
	// glPopMatrix();

	// printf("%f %f %f\n", p.x,p.y,p.z);
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