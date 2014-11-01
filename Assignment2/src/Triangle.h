#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <glm/glm.hpp>
#include "Ray.h"

class Triangle{
	glm::vec3 v1;
	glm::vec3 v2;
	glm::vec3 v3;

	glm::vec3 col1;
	glm::vec3 col2;

	glm::vec3 k_ambient;
	glm::vec3 k_diffuse;
	glm::vec3 k_specular;
	glm::vec3 k_reflect;

	int specular_pow;

	glm::mat4 trans;
	glm::mat4 inv_trans;
	glm::mat4 t_inv_trans;
	bool is_transformed;

	public:
		Triangle(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float v3x, float v3y, float v3z);
		Triangle(glm::vec3 z1, glm::vec3 z2, glm::vec3 z3);
		Triangle(const Triangle& obj);
		virtual ~Triangle();

		void setAmbient(glm::vec3 ka);
		void setDiffuse(glm::vec3 kd);
		void setSpecular(glm::vec3);
		void setSpecularPow(int sp);
		void setReflect(glm::vec3 kr);
		void setTransform(glm::mat4 trans_mat);

		bool isTransformed();
		glm::vec3 getAmbient();
		glm::vec3 getDiffuse();
		glm::vec3 getSpecular();
		int getSpecularPow();
		glm::vec3 getReflect();

		glm::vec3 getNormal(glm::vec3 point);
		float intersect(Ray* cam_ray);

		void print();
};

#endif