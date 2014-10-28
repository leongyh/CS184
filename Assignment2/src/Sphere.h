#ifndef SPHERE_H_
#define SPHERE_H_

#include <glm/glm.hpp>
#include "Ray.h"
#include "Transform.h"

class Sphere{
	glm::vec3 position;
	float radius;

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
		Sphere(float x, float y, float z, float r);
		Sphere(const Sphere& obj);
		virtual ~Sphere();

		void setAmbient(glm::vec3 ka);
		void setDiffuse(glm::vec3 kd);
		void setSpecular(glm::vec3 ks);
		void setSpecularPow(int sp);
		void setReflect(glm::vec3 kr);
		void setTransform(glm::mat4 trans_mat);

		bool isTransformed();
		glm::vec3 getAmbient();
		glm::vec3 getDiffuse();
		glm::vec3 getSpecular();
		int getSpecularPow();
		glm::vec3 getReflect();
		glm::mat4 getTransform();

		glm::vec3 getNormal(glm::vec3 point);
		float intersect(Ray* cam_ray);

		void print();
};

#endif