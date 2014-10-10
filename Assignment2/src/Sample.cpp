#include "Sample.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>


Sample::Sample(float x, float y, float r, float g, float b){
	width = x;
	height = y;

	color = glm::vec3(r, g, b);
}

Sample::~Sample(){

}

glm::vec3 Sample::getColor(){
	return color;
}

float Sample::getX(){
	return x;
}

float Sample::getY(){
	return y;
}

void Sample::print(){
	printf("The Scene coordinates);
}