#ifndef READER_H_
#define READER_H_

#include <glm/glm.hpp>
#include "pugixml.hpp"
#include "Scene.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Sphere.h"
#include "Triangle.h"

class Reader{
	pugi::xml_node root;
	const char* test_num;

	public:
		Reader(const char* file_loc, const char* num);
		virtual ~Reader();

		void parse(Scene& scene);
};

#endif