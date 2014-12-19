#include "Scene.h"
#include <cstdlib>
#include <cstdio>


Scene::Scene(){
	this->arm = new Arm();
	this->goal = arm->generateGoal();
	this->step = 0.0;
	this->solver = new IKSolver();
}

Scene::~Scene(){

}


void Scene::render(float x, float y, float z){
	// printf("Rendering start...\n");
	goal->move(x, y, z);
	solver->solve(*arm, *goal);
}

void Scene::draw(){
	this->arm->draw();
	this->goal->draw();
	// goal->print();

	// glm::vec3 p = this->arm->getEndPoint();
	// glm::vec3 p = this->arm->getJointPos(3);

	// glPushMatrix();
	// 	glTranslatef(p.x, p.y, p.z);
	// 	glutSolidSphere(0.5f, 20, 20);
	// glPopMatrix();

	// printf("%f %f %f\n", p.x,p.y,p.z);
}

void Scene::print(){
	printf("The Scene.");
}