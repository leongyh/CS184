#include "Arm.h"
#include <cstdlib>
#include <cstdio>

Arm::Arm(){
	Joint* j1 = new Joint(60.0f, 0.0f, 0.0f, 1.0f);
	Joint* j2 = new Joint(10.0f, 0.0f, 20.0f, 2.0f);
	Joint* j3 = new Joint(0.0f, 40.0f, 0.0f, 1.0f);
	Joint* j4 = new Joint(0.0f, 0.0f, 10.0f, 2.5f);

	this->end = new Joint(0.0f, 0.0f, 0.0f, 0.0f);

	this->joints.push_back(j1);
	this->joints.push_back(j2);
	this->joints.push_back(j3);
	this->joints.push_back(j4);

	float len = 0.0f;

	for(int i = 0; i < joints.size(); i++){
		len += joints[i]->getLength();
	}

	length = len;

	simdA = 0.1;
}

Arm::~Arm(){

}

void Arm::applyDeltaAngle(Eigen::VectorXf dA){
	for (int i = 0; i < dA.size(); i+=3){
		joints[i/3]->updateAngles(dA[i], dA[i+1], dA[i+2]);
	}
}

void Arm::draw(){
	Joint* j1 = joints[0];
	Joint* j2 = joints[1];
	Joint* j3 = joints[2];
	Joint* j4 = joints[3];

	//base rigid cone
	glPushMatrix();
		glRotatef(j1->getAngle(), j1->getAxis().x, j1->getAxis().y, j1->getAxis().z);
		// glRotatef(j1->getAngles().x, 1.0, 0.0, 0.0);
		// glRotatef(j1->getAngles().y, 0.0, 1.0, 0.0);
		// glRotatef(j1->getAngles().z, 0.0, 0.0, 1.0);
		glutSolidSphere(0.1f, 20, 20);
		glutSolidCone(0.5f, j1->getLength(), 20, 20);

	//second cone
		glTranslatef(0.0f, 0.0f, j1->getLength());
		glRotatef(j2->getAngle(), j2->getAxis().x, j2->getAxis().y, j2->getAxis().z);
		// glRotatef(j2->getAngles().x, 1.0, 0.0, 0.0);
		// glRotatef(j2->getAngles().y, 0.0, 1.0, 0.0);
		// glRotatef(j2->getAngles().z, 0.0, 0.0, 1.0);
		glutSolidSphere(0.1f, 20, 20);
		glutSolidCone(0.5f, j2->getLength(), 20, 20);
	// glPopMatrix();

	//third cone
		glTranslatef(0.0f, 0.0f, j2->getLength());
		glRotatef(j3->getAngle(), j3->getAxis().x, j3->getAxis().y, j3->getAxis().z);
		// glRotatef(j3->getAngles().x, 1.0, 0.0, 0.0);
		// glRotatef(j3->getAngles().y, 0.0, 1.0, 0.0);
		// glRotatef(j3->getAngles().z, 0.0, 0.0, 1.0);
		glutSolidSphere(0.1f, 20, 20);
		glutSolidCone(0.5f, j3->getLength(), 20, 20);
	// glPopMatrix();

	//fourth cone
		glTranslatef(0.0f, 0.0f, j3->getLength());
		glRotatef(j4->getAngle(), j4->getAxis().x, j4->getAxis().y, j4->getAxis().z);
		// glRotatef(j4->getAngles().x, 1.0, 0.0, 0.0);
		// glRotatef(j4->getAngles().y, 0.0, 1.0, 0.0);
		// glRotatef(j4->getAngles().z, 0.0, 0.0, 1.0);
		glutSolidSphere(0.1f, 20, 20);
		glutSolidCone(0.5f, j4->getLength(), 20, 20);

	//end effector
		// glTranslatef(0.0f, 0.0f, j4->getLength());
		// glutSolidSphere(0.1f, 20, 20);
	glPopMatrix();
}

glm::vec3 Arm::getEndPoint(){
	glm::vec4 p = glm::vec4(0.0, 0.0, 0.0, 1.0);
	glm::mat4 transform = glm::mat4(1.0f);

	Joint* j1 = joints[0];
	Joint* j2 = joints[1];
	Joint* j3 = joints[2];
	Joint* j4 = joints[3];

	transform = transform * glm::rotate(j1->getAngle(), j1->getAxis());
	// transform = transform * glm::rotate(j1->getAngles().x, glm::vec3(1.0f, 0.0f, 0.0f));
	// transform = transform * glm::rotate(j1->getAngles().y, glm::vec3(0.0f, 1.0f, 0.0f));
	// transform = transform * glm::rotate(j1->getAngles().z, glm::vec3(0.0f, 0.0f, 1.0f));
	
	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j1->getLength()));
	transform = transform * glm::rotate(j2->getAngle(), j2->getAxis());
	// transform = transform * glm::rotate(j2->getAngles().x, glm::vec3(1.0f, 0.0f, 0.0f));
	// transform = transform * glm::rotate(j2->getAngles().y, glm::vec3(0.0f, 1.0f, 0.0f));
	// transform = transform * glm::rotate(j2->getAngles().z, glm::vec3(0.0f, 0.0f, 1.0f));

	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j2->getLength()));
	transform = transform * glm::rotate(j3->getAngle(), j3->getAxis());
	// transform = transform * glm::rotate(j3->getAngles().x, glm::vec3(1.0f, 0.0f, 0.0f));
	// transform = transform * glm::rotate(j3->getAngles().y, glm::vec3(0.0f, 1.0f, 0.0f));
	// transform = transform * glm::rotate(j3->getAngles().z, glm::vec3(0.0f, 0.0f, 1.0f));
	
	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j3->getLength()));
	transform = transform * glm::rotate(j4->getAngle(), j4->getAxis());
	// transform = transform * glm::rotate(j4->getAngles().x, glm::vec3(1.0f, 0.0f, 0.0f));
	// transform = transform * glm::rotate(j4->getAngles().y, glm::vec3(0.0f, 1.0f, 0.0f));
	// transform = transform * glm::rotate(j4->getAngles().z, glm::vec3(0.0f, 0.0f, 1.0f));
	
	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j4->getLength()));

	return glm::vec3(transform * p);
}

glm::vec3 Arm::getJointPos(int i){
	glm::vec4 p = glm::vec4(0.0, 0.0, 0.0, 1.0);
	glm::mat4 transform = glm::mat4(1.0f);

	Joint* j1 = joints[0];
	Joint* j2 = joints[1];
	Joint* j3 = joints[2];
	Joint* j4 = joints[3];

	transform = transform * glm::rotate(j1->getAngle(), j1->getAxis());

	if(i == 0) return glm::vec3(transform * p);

	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j1->getLength()));
	transform = transform * glm::rotate(j2->getAngle(), j2->getAxis());

	if(i == 1) return glm::vec3(transform * p);

	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j2->getLength()));
	transform = transform * glm::rotate(j3->getAngle(), j3->getAxis());

	if(i == 2) return glm::vec3(transform * p);
	
	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j3->getLength()));
	transform = transform * glm::rotate(j4->getAngle(), j4->getAxis());

	if(i == 3) return glm::vec3(transform * p);
}

std::vector<Joint*> Arm::getJoints(){
	return joints;
}

float Arm::getMaxLength(){
	return length;
}

Goal* Arm::generateGoal(){
	glm::vec4 p = glm::vec4(0.0, 0.0, 0.0, 1.0);
	glm::mat4 transform = glm::mat4(1.0f);

	Joint* j1 = joints[0];
	Joint* j2 = joints[1];
	Joint* j3 = joints[2];
	Joint* j4 = joints[3];

	transform = transform * glm::rotate(j1->getAngle(), j1->getAxis());
	
	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j1->getLength()));
	transform = transform * glm::rotate(j2->getAngle(), j2->getAxis());

	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j2->getLength()));
	transform = transform * glm::rotate(j3->getAngle(), j3->getAxis());
	
	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j3->getLength()));
	transform = transform * glm::rotate(j4->getAngle(), j4->getAxis());
	
	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j4->getLength()));

	return new Goal(glm::vec3(transform * p));
}

glm::vec3 Arm::simX(int i){
	glm::vec3 current_pos = this->getEndPoint();
	glm::vec4 p = glm::vec4(0.0, 0.0, 0.0, 1.0);
	glm::mat4 transform = glm::mat4(1.0f);

	Joint* j1 = joints[0];
	Joint* j2 = joints[1];
	Joint* j3 = joints[2];
	Joint* j4 = joints[3];

	if(i == 0){
		glm::vec3 axis = j1->getAngles();
		axis = axis + glm::vec3(simdA, 0.0f, 0.0f);
		float angle = glm::length(axis);

		transform = transform * glm::rotate(angle, glm::normalize(axis));	
	} else{
		transform = transform * glm::rotate(j1->getAngle(), j1->getAxis());	
	}
	
	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j1->getLength()));

	if(i == 1){
		glm::vec3 axis = j2->getAngles();
		axis = axis + glm::vec3(simdA, 0.0f, 0.0f);
		float angle = glm::length(axis);

		transform = transform * glm::rotate(angle, glm::normalize(axis));	
	} else{
		transform = transform * glm::rotate(j2->getAngle(), j2->getAxis());	
	}

	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j2->getLength()));

	if(i == 2){
		glm::vec3 axis = j3->getAngles();
		axis = axis + glm::vec3(simdA, 0.0f, 0.0f);
		float angle = glm::length(axis);

		transform = transform * glm::rotate(angle, glm::normalize(axis));	
	} else{
		transform = transform * glm::rotate(j3->getAngle(), j3->getAxis());	
	}
	
	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j3->getLength()));

	if(i == 3){
		glm::vec3 axis = j4->getAngles();
		axis = axis + glm::vec3(simdA, 0.0f, 0.0f);
		float angle = glm::length(axis);

		transform = transform * glm::rotate(angle, glm::normalize(axis));	
	} else{
		transform = transform * glm::rotate(j4->getAngle(), j4->getAxis());	
	}
	
	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j4->getLength()));

	return glm::vec3(transform * p) - current_pos;
}

glm::vec3 Arm::simY(int i){
	glm::vec3 current_pos = this->getEndPoint();
	glm::vec4 p = glm::vec4(0.0, 0.0, 0.0, 1.0);
	glm::mat4 transform = glm::mat4(1.0f);

	Joint* j1 = joints[0];
	Joint* j2 = joints[1];
	Joint* j3 = joints[2];
	Joint* j4 = joints[3];

	if(i == 0){
		glm::vec3 axis = j1->getAngles();
		axis = axis + glm::vec3(0.0f, simdA, 0.0f);
		float angle = glm::length(axis);

		transform = transform * glm::rotate(angle, glm::normalize(axis));	
	} else{
		transform = transform * glm::rotate(j1->getAngle(), j1->getAxis());	
	}
	
	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j1->getLength()));

	if(i == 1){
		glm::vec3 axis = j2->getAngles();
		axis = axis + glm::vec3(0.0f, simdA, 0.0f);
		float angle = glm::length(axis);

		transform = transform * glm::rotate(angle, glm::normalize(axis));	
	} else{
		transform = transform * glm::rotate(j2->getAngle(), j2->getAxis());	
	}

	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j2->getLength()));

	if(i == 2){
		glm::vec3 axis = j3->getAngles();
		axis = axis + glm::vec3(0.0f, simdA, 0.0f);
		float angle = glm::length(axis);

		transform = transform * glm::rotate(angle, glm::normalize(axis));	
	} else{
		transform = transform * glm::rotate(j3->getAngle(), j3->getAxis());	
	}
	
	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j3->getLength()));

	if(i == 3){
		glm::vec3 axis = j4->getAngles();
		axis = axis + glm::vec3(0.0f, simdA, 0.0f);
		float angle = glm::length(axis);

		transform = transform * glm::rotate(angle, glm::normalize(axis));	
	} else{
		transform = transform * glm::rotate(j4->getAngle(), j4->getAxis());	
	}
	
	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j4->getLength()));

	return glm::vec3(transform * p) - current_pos;
}

glm::vec3 Arm::simZ(int i){
	glm::vec3 current_pos = this->getEndPoint();
	glm::vec4 p = glm::vec4(0.0, 0.0, 0.0, 1.0);
	glm::mat4 transform = glm::mat4(1.0f);

	Joint* j1 = joints[0];
	Joint* j2 = joints[1];
	Joint* j3 = joints[2];
	Joint* j4 = joints[3];

	if(i == 0){
		glm::vec3 axis = j1->getAngles();
		axis = axis + glm::vec3(0.0f, 0.0f, simdA);
		float angle = glm::length(axis);

		transform = transform * glm::rotate(angle, glm::normalize(axis));	
	} else{
		transform = transform * glm::rotate(j1->getAngle(), j1->getAxis());	
	}
	
	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j1->getLength()));

	if(i == 1){
		glm::vec3 axis = j2->getAngles();
		axis = axis + glm::vec3(0.0f, 0.0f, simdA);
		float angle = glm::length(axis);

		transform = transform * glm::rotate(angle, glm::normalize(axis));	
	} else{
		transform = transform * glm::rotate(j2->getAngle(), j2->getAxis());	
	}

	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j2->getLength()));

	if(i == 2){
		glm::vec3 axis = j3->getAngles();
		axis = axis + glm::vec3(0.0f, 0.0f, simdA);
		float angle = glm::length(axis);

		transform = transform * glm::rotate(angle, glm::normalize(axis));	
	} else{
		transform = transform * glm::rotate(j3->getAngle(), j3->getAxis());	
	}
	
	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j3->getLength()));

	if(i == 3){
		glm::vec3 axis = j4->getAngles();
		axis = axis + glm::vec3(0.0f, 0.0f, simdA);
		float angle = glm::length(axis);

		transform = transform * glm::rotate(angle, glm::normalize(axis));	
	} else{
		transform = transform * glm::rotate(j4->getAngle(), j4->getAxis());	
	}
	
	transform = transform * glm::translate(glm::vec3(0.0f, 0.0f, j4->getLength()));

	return glm::vec3(transform * p) - current_pos;
}

void Arm::print(){
	printf("The Arm.");
}