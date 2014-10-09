#include "MyVector.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>

MyVector::MyVector(float x, float y, float z){
	coordinates = glm::vec3(x, y, z);
}

MyVector::~MyVector(){

}
		
void MyVector::setDirection(float x, float y, float z){
	coordinates = glm::vec3(x, y, z);
}

float MyVector::dotProduct(glm::vec3 vec){
	return glm::dot(coordinates, vec);
}

glm::vec3 MyVector::getCoordinates(){
	return coordinates;
}

void MyVector::print(){
	printf("The vector coordinates are (%f,%f,%f)", coordinates.x, coordinates.y, coordinates.z);
}