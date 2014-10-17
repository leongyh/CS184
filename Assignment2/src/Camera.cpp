#include "Camera.h"
#include <cstdlib>
#include <cstdio>

Camera::Camera(float x, float y, float z, float view_x, float view_y, float view_z, float vert_x, float vert_y, float vert_z, float d){
	position = glm::vec3(x, y, z);
	view = glm::vec3(view_x, view_y, view_z);
	vertical = glm::vec3(vert_x, vert_y, vert_z);
	horizontal = glm::cross(-1.0f * view, vertical);
	depth = d;
}

Camera::~Camera(){

}

Ray* Camera::emitRay(Sample* s){
	float u = s->getU();
	float v = s->getV();

	glm::vec3 direction = depth * view + u * horizontal + v * vertical;

	Ray* r = new Ray(position.x, position.y, position.z, direction.x, direction.y, direction.z);

	return r;
}

void Camera::print(){
	printf("The Camera coordinates are (%f,%f,%f) with view vector (%f,%f,%f) and vertical vector (%f,%f,%f) and horizontal vector (%f,%f,%f) with depth=%f\n", position.x, position.y, position.z, view.x, view.y, view.z, vertical.x, vertical.y, vertical.z, horizontal.x, horizontal.y, horizontal.z, depth);
}