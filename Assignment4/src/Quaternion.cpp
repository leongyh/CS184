#include "Quaternion.h"

#include <math.h>

Quaternion::Quaternion(){
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 0.0f;
};

Quaternion::Quaternion(float _x, float _y, float _z, float _w){
	this->x = _x;
	this->y = _y;
	this->z = _z;
	this->w = _w;
};

Quaternion::~Quaternion(){

};

void Quaternion::loadIdentity()
{
	this->w = 1.0f;
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
};

Quaternion* Quaternion::setRotation(float angleX, float angleY, float angleZ){
	float angle = sqrt((angleX*angleX) + (angleY*angleY) + (angleZ*angleZ));

	if(angle!=0.0f){
		angleX /= angle;
		angleY /= angle;
		angleZ /= angle;
	
		// convert angle to radians
		angle *= (M_PI / (float)180.0f);
		
		this->w = cos(angle / 2.0f);
		
		float temp = sin(angle / 2.0f);
		
		this->x = angleX * temp;
		this->y = angleY * temp;
		this->z = angleZ * temp;
	}

	return this;
};

Quaternion Quaternion::conjugate(){
	Quaternion retval = *this;
	retval.x = -retval.x;
	retval.y = -retval.y;
	retval.z = -retval.z;
	return retval;
};

Quaternion Quaternion::operator*(const Quaternion &op2)
{
	Quaternion retval;
	
	retval.w = (w*op2.w) - (x*op2.x) - (y*op2.y) - (z*op2.z);
	retval.x = (w*op2.x) + (op2.w*x) + (y*op2.z) - (op2.y*z);
	retval.y = (w*op2.y) + (op2.w*y) + (z*op2.x) - (op2.z*x);
	retval.z = (w*op2.z) + (op2.w*z) + (x*op2.y) - (op2.x*y);
	
	return retval;
};

Quaternion Quaternion::operator*=(const Quaternion &op2)
{
	Quaternion retval;
	float X = x;
	float Y = y;
	float Z = z;
	float W = w;
	
	w = (W*op2.w) - (X*op2.x) - (Y*op2.y) - (Z*op2.z);
	x = (W*op2.x) + (op2.w*X) + (Y*op2.z) - (op2.y*Z);
	y = (W*op2.y) + (op2.w*Y) + (Z*op2.x) - (op2.z*X);
	z = (W*op2.z) + (op2.w*Z) + (X*op2.y) - (op2.x*Y);
	
	return retval;
};
