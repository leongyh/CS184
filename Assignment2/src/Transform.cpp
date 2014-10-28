#include "Transform.h"
#include <cstdlib>
#include <cstdio>


Transform::Transform(){
	transformation = glm::mat4(1.0f);
	// matrices = new std::stack<glm::mat4>();
}

Transform::Transform(glm::mat4 matr){
	transformation = matr;
}

Transform::Transform(const Transform& obj){
	transformation = obj.transformation;
}

Transform::~Transform(){
	
}

void Transform::pushTranslate(float x, float y, float z){
	glm::mat4 m = glm::translate(glm::vec3(x, y, z));

	// matrices.push(m);
	transformation = m * transformation;
}

void Transform::pushScale(float x, float y, float z){
	glm::mat4 m = glm::scale(glm::vec3(x, y, z));

	// matrices.push(m);
	transformation = m * transformation;
}

void Transform::pushRotate(float x, float y, float z){
	glm::vec3 r = glm::vec3(x, y, z);
	float angle = glm::radians(glm::length(r));
	glm::mat4 m = glm::rotate(angle, r);

	// matrices.push(m);
	transformation = m * transformation;
}

// void Transform::popMatrix(){
// 	while(!matrices.empty()){
// 		glm::mat4 m = matrices.pop();

// 		transformation = m * transformation;
// 	}
// }

void Transform::resetTransform(){
	transformation = glm::mat4(1.0f);
}

glm::mat4 Transform::getTransform(){
	// if(matrices.empty()){
	// 	this->popMatrix();
	// }

	return transformation;
}

void Transform::print(){
	printf("Transformation matrix:\n");
	
	int i,j;
  	for (j=0; j<4; j++){
    	for (i=0; i<4; i++){
    		printf("%f ",transformation[i][j]);
  		}
  		printf("\n");
 	}
}