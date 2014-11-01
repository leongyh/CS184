#define GLM_SWIZZLE

#include "Triangle.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>

Triangle::Triangle(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float v3x, float v3y, float v3z){
	v1 = glm::vec3(v1x, v1y, v1z);
	v2 = glm::vec3(v2x, v2y, v2z);
	v3 = glm::vec3(v3x, v3y, v3z);

	k_ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	k_diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
	k_specular = glm::vec3(0.0f, 0.0f, 0.0f);
	k_reflect = glm::vec3(0.0f, 0.0f, 0.0f);

	specular_pow = 1;

	trans = glm::mat4(1.0f);
	is_transformed = false;

	col1 = v1 - v2;
	col2 = v1 - v3;
}

Triangle::Triangle(glm::vec3 z1, glm::vec3 z2, glm::vec3 z3){
	v1 = z1;
	v2 = z2;
	v3 = z3;

	k_ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	k_diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
	k_specular = glm::vec3(0.0f, 0.0f, 0.0f);
	k_reflect = glm::vec3(0.0f, 0.0f, 0.0f);

	specular_pow = 1;

	trans = glm::mat4(1.0f);
	is_transformed = false;

	col1 = v1 - v2;
	col2 = v1 - v3;	
}

Triangle::Triangle(const Triangle& obj){
	v1 = obj.v1;
	v2 = obj.v2;
	v3 = obj.v3;
	k_ambient = obj.k_ambient;
	k_diffuse = obj.k_diffuse;
	k_specular = obj.k_specular;
	k_reflect = obj.k_reflect;
	specular_pow = obj.specular_pow;
	trans = obj.trans;
	is_transformed = obj.is_transformed;
}

Triangle::~Triangle(){

}

void Triangle::setAmbient(glm::vec3 ka){
	k_ambient = ka;
}

void Triangle::setDiffuse(glm::vec3 kd){
	k_diffuse = kd;
}

void Triangle::setSpecular(glm::vec3 ks){
	k_specular = ks;
}

void Triangle::setSpecularPow(int sp){
	specular_pow = sp;
}

void Triangle::setReflect(glm::vec3 kr){
	k_reflect = kr;
}

void Triangle::setTransform(glm::mat4 trans_mat){
	trans = trans_mat;
	inv_trans = glm::inverse(trans);
	t_inv_trans = glm::transpose(inv_trans);

	is_transformed = true;

	// glm::mat4 tlt_mat, inv_tlt_mat;
	// // printf("%f\n", glm::length(position));

	// if(glm::length(position) > 0.0f){
	// 	tlt_mat = glm::translate(position);
	// 	inv_tlt_mat = glm::inverse(tlt_mat);
		
	// 	// printf("%s\n", "hi");
	// 	trans = tlt_mat * trans_mat * inv_tlt_mat;
	// } else {
	// 	trans = trans_mat;
	// }

	// inv_trans = glm::inverse(trans);
	// t_inv_trans = glm::transpose(inv_trans);

	// is_transformed = true;

	// int i,j;
 //  	for (j=0; j<4; j++){
 //    	for (i=0; i<4; i++){
 //    		printf("%f ", inv_tlt_mat[i][j]);
 //  		}
 //  		printf("\n");
 // 	}
}

bool Triangle::isTransformed(){
	return is_transformed;
}

glm::vec3 Triangle::getAmbient(){
	return k_ambient;
}

glm::vec3 Triangle::getDiffuse(){
	return k_diffuse;
}

glm::vec3 Triangle::getSpecular(){
	return k_specular;
}

int Triangle::getSpecularPow(){
	return specular_pow;
}

glm::vec3 Triangle::getReflect(){
	return k_reflect;
}

glm::vec3 Triangle::getNormal(glm::vec3 point){
	glm::vec3 normal;

	if(is_transformed){
		glm::vec4 temp = glm::vec4(point, 1.0f);
		temp = inv_trans * temp;

		glm::vec3 trans_point = temp.xyz();

		glm::vec3 r1 = trans_point - v1;
		glm::vec3 r2 = trans_point - v2;

		normal = glm::cross(r1, r2);

		glm::vec4 temp_normal = glm::vec4(normal, 1.0f);

		temp_normal = t_inv_trans * temp_normal;

		normal = glm::normalize(temp_normal.xyz());
	} else{
		glm::vec3 r1 = point - v1;
		glm::vec3 r2 = point - v2;
		
		normal = glm::normalize(glm::cross(r1, r2));
	}

	return normal;
}

float Triangle::intersect(Ray* cam_ray){
	glm::vec3 col3;
	glm::vec3 col4;
	glm::mat3 intersect_mat;
	glm::vec3 sol;

	glm::vec3 ray_dir = cam_ray->getDirection();
	glm::vec3 ray_pos = cam_ray->getPosition();

	if(is_transformed){
		glm::vec4 temp_dir = glm::vec4(ray_dir, 0.0f);
		glm::vec4 temp_pos = glm::vec4(ray_pos, 1.0f);

		temp_dir = inv_trans * temp_dir;
		temp_pos = inv_trans * temp_pos;

		ray_dir = temp_dir.xyz();
		ray_pos = temp_pos.xyz();

		col3 = ray_dir;
		col4 = v1 - ray_pos;

		intersect_mat = glm::mat3(col1, col2, col3);
		sol = glm::inverse(intersect_mat) * col4;
	} else{
		col3 = cam_ray->getDirection();
		col4 = v1 - cam_ray->getPosition();
		intersect_mat = glm::mat3(col1, col2, col3);

		// int i,j;
	 //  	for (j=0; j<3; j++){
	 //    	for (i=0; i<3; i++){
	 //    		printf("%f ", intersect_mat[i][j]);
	 //  		}
	 //  		printf("\n");
	 // 	}

	 // 	printf("--------\n");

		sol = glm::inverse(intersect_mat) * col4;
	}

	

	float beta = sol.x;
	float gamma = sol.y;
	float t = sol.z;

	if(t < 0.0001f || t > 999.0f){
		return -1.0;
	} else if(gamma < 0.0f || gamma > 1.0f){
		return -1.0f;
	} else if(beta < 0.0f || beta > 1.0f - gamma){
		return -1.0f;
	} else{
		// printf("%f\n", t);
		return t;
	}
}

void Triangle::print(){
	printf("The trangle has vectors v1: (%f,%f,%f), v2: (%f,%f,%f), v3: (%f,%f,%f)\n", v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z);
}