#ifndef TEXT_READER_H_
#define TEXT_READER_H_

#include <glm/glm.hpp>

#include "ObjReader.h"
#include "Transform.h"
#include "Scene.h"
#include "Camera.h"
#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Sphere.h"
#include "Triangle.h"

class TextReader{
	ObjReader* obj;

	public:
		TextReader();
		virtual ~TextReader();

		void parse(Scene& scene, const char* file_loc);
};

#endif