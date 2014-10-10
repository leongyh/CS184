#include "Camera.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>


Camera::Camera(float x, float y, float z, float vx, float vy, float vz, float yx, float yy, float yz, float d){
	position = glm::vec3(x, y, z);
	view = glm::vec3(vx, vy, vz);
	yaw = glm::vec3(yx, yy, yz);
	pitch = glm::cross(view, yaw);
	depth = d;
}

Camera::~Camera(){

}

void Camera::print(){
	printf("The Camera coordinates are (%f,%f,%f)", position.x, position.y, position.z);
}