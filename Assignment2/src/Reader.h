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
	int test_num;

	public:
		Reader(const char* file_loc, int num);
		virtual ~Reader();

		void run(Scene& scene);
		void test(Scene& scene);
};

#endif