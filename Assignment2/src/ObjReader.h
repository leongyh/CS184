#ifndef OBJ_READER_H_
#define OBJ_READER_H_

#include <glm/glm.hpp>
#include "Transform.h"
#include "Scene.h"
#include "Triangle.h"

class ObjReader{
	std::vector<glm::vec3> v;
	std::vector<glm::vec3> vn;
	std::vector<unsigned int> v_index;
	std::vector<unsigned int> vn_index;

	glm::mat4 trans;
	bool is_transformed;

	public:
		ObjReader();
		virtual ~ObjReader();

		void parse(const char* file_loc, int f_type);
		void createObj(Scene& scene, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, int sp, glm::vec3 kr);
		void setTransform(glm::mat4 mat);
		void reset();
};

#endif