#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include "Ray.h"
#include "Sample.h"

class Camera{
	glm::vec3 position;
	glm::vec3 view;
	glm::vec3 horizontal;
	glm::vec3 vertical;

	float depth;

	public:
		Camera(float x, float y, float z, float view_x, float view_y, float view_z, float vert_x, float vert_y, float vert_z, float d);
		virtual ~Camera();

		Ray* emitRay(Sample* s);

		void print();
};

#endif