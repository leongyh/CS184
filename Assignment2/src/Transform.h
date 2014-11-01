#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#define GLM_FORCE_RADIANS

// #include <stack>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_cross_product.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "Ray.h"

class Transform{
	glm::mat4 transformation;
	// std::stack<glm::mat4> matrices;

	public:
		Transform();
		Transform(glm::mat4 matr);
		Transform(const Transform& obj);
		virtual ~Transform();

		void pushTranslate(float x, float y, float z);
		void pushScale(float x, float y, float z);
		void pushRotate(float x, float y, float z);

		void resetTransform();

		glm::mat4 getTransform();

		void print();
};

#endif