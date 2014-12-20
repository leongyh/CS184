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
	} else if(type == 2){
		if (t <= 1800){
			pos = glm::vec3(7 * cos(t * PI / 180), 4 * sin(t * PI / 180), (t / 360));
		} else{
			pos = glm::vec3(7 * cos(1800 * PI / 180), 4 * sin(1800 * PI / 180), 1800);
		}
	} else if(type == 3){
		pos = glm::vec3(4 * cos(t * PI / 180), 0.0f, 7 * sin(t * PI / 180) * cos(t * PI / 180));
	}

	return pos;
}

void Path::draw(){
	glLineWidth(1.35f);

	if(type == 1){
		glBegin(GL_LINE_LOOP);
		for(int t = 0; t < 360; t++){
			glVertex3f(4 * cos(t *PI / 180), 0.0f, 7 * sin(t * PI / 180));
		}
	} else if(type == 2){
		glBegin(GL_LINE_STRIP);
		for(int t = 0; t < 1800; t++){
			glVertex3f(7 * cos(t * PI / 180), 4 * sin(t * PI / 180), (float) t / 360);
		}
	} else if(type == 3){
		glBegin(GL_LINE_LOOP);
		for(int t = 0; t < 360; t++){
			glVertex3f(4 * cos(t * PI / 180), 0.0f, 7 * sin(t * PI / 180) * cos(t * PI / 180));
		}
	}

	glEnd();
}

void Path::print(){
	printf("The Path");
}