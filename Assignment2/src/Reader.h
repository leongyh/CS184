#ifndef READER_H_
#define READER_H_

#include <glm/glm.hpp>
#include "pugixml.hpp"
#include "ObjReader.h"
#include "Transform.h"
#include "Scene.h"
#include "Camera.h"
#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Sphere.h"
#include "Triangle.h"

class Reader{
	ObjReader* obj;
	pugi::xml_node root;
	char* test_num;

	public:
		Reader(const char* file_loc, char* num);
		virtual ~Reader();

		void parse(Scene& scene);
};

#endif