#include "Scene.h"
#include <cstdlib>
#include <cstdio>


Scene::Scene(){
	this->arm = new Arm();
	this->step = 0.0;
	this->solver = new IKSolver();
}

Scene::~Scene(){

}


void Scene::render(){
	// printf("Rendering start...\n");
	// std::vector<float> vec;
	// vec.push_back()
	// this->arm->applyDeltaAngle
}

void Scene::draw(){
	this->arm->draw();
	solver->solve(*arm);
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