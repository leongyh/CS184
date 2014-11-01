#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include "Ray.h"
#include "Sample.h"

class Camera{
	glm::vec3 position;
	glm::vec3 ll, lr, ul, ur;

	public:
		Camera(float x, float y, float z, float llx, float lly, float llz, float lrx, float lry, float lrz, float ulx, float uly, float ulz, float urx, float ury, float urz);
		virtual ~Camera();

		Ray* emitRay(Sample* s);

		void print();
};

#endif