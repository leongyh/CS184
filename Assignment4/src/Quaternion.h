#ifndef QUATERNION_H_
#define QUATERNION_H_

#include <glm/glm.hpp>

class Quaternion{
	float x, y, z, w;
	
	public:
		Quaternion();
		Quaternion(float _x, float _y, float _z, float _w);
		virtual ~Quaternion();

		void loadIdentity();

		Quaternion* setRotation(float angleX, float angleY, float angleZ);
		Quaternion conjugate();

		Quaternion operator*(const Quaternion &op2);
		Quaternion operator*=(const Quaternion &op2);
};

#endif