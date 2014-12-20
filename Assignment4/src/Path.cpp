#include "Path.h"
#include <cstdlib>
#include <cstdio>


Path::Path(int n){
	this->type = n;
}

Path::~Path(){

}

glm::vec3 Path::getPosition(float t){
	glm::vec3 pos;

	if(type == 1){
		pos = glm::vec3(4 * cos(t * PI / 180), 0.0f, 7 * sin(t * PI / 180));
	}

	return pos;
}

void Path::draw(){
	glLineWidth(1.35f);
	glBegin(GL_LINE_LOOP);

	if(type == 1){
		for(int i = 0; i < 360; i++){
			glVertex3f(4 * cos(i *PI / 180), 0.0f, 7 * sin(i * PI / 180));
		}
	}

	glEnd();
}

void Path::print(){
	printf("The Path");
}