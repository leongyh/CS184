#include "Camera.h"
#include <cstdlib>
#include <cstdio>

Camera::Camera(float x, float y, float z, float llx, float lly, float llz, float lrx, float lry, float lrz, float ulx, float uly, float ulz, float urx, float ury, float urz){
	position = glm::vec3(x, y, z);
	ll = glm::vec3(llx, lly, llz);
	lr = glm::vec3(lrx, lry, lrz);
	ul = glm::vec3(ulx, uly, ulz);
	ur = glm::vec3(urx, ury, urz);
}

Camera::~Camera(){

}

Ray* Camera::emitRay(Sample* s){
	float u = s->getU();
	float v = s->getV();

	glm::vec3 direction = (u * (v * ll + (1-v) * ul) + (1-u) * (v * lr + (1-v) * ur)) - position;

	// u * (lr - ll);
	// v * (ur - ul);

	Ray* r = new Ray(position.x, position.y, position.z, direction.x, direction.y, direction.z);
	// printf("ul is (%f,%f,%f)\n", ul.x, ul.y, ul.z);
	// r->print();

	return r;
}

void Camera::print(){
	printf("The Camera coordinates are (%f,%f,%f)\n", position.x, position.y, position.z);
}