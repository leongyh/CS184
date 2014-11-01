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

	transformation = transformation * m;
}

void Transform::pushScale(float x, float y, float z){
	glm::mat4 m = glm::scale(glm::vec3(x, y, z));

	transformation = transformation * m;
}

void Transform::pushRotate(float x, float y, float z){
	glm::vec3 r = glm::vec3(x, y, z);
	float angle = glm::radians(glm::length(r));

	if(angle != 0.0f){
		r = glm::normalize(r);
		// glm::mat3 r_outer = glm::outerProduct(r, r);
		glm::mat3 r_cross =  glm::matrixCross3(r);

		glm::mat3 rot = glm::mat3(1.0f) + (glm::sin(angle) * r_cross) + ((1 - glm::cos(angle)) * (r_cross * r_cross));
		glm::mat4 m = glm::mat4(rot);

		transformation = transformation * m;

		// int i,j;
		// for (j=0; j<4; j++){
		// 	for (i=0; i<4; i++){
		// 		printf("%f ",m[i][j]);
		// 	}
		// 	printf("\n");
		// }
	}
}

void Transform::resetTransform(){
	transformation = glm::mat4(1.0f);
}

glm::mat4 Transform::getTransform(){
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