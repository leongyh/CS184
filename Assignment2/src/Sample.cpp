#include "Sample.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>

Sample::Sample(int i, int j, float u, float v){
	this->i = i;
	this->j = j;
	this->u = u;
	this->v = v;
}

Sample::~Sample(){

}

int Sample::getI(){
	return i;
}

int Sample::getJ(){
	return j;
}

float Sample::getU(){
	return u;
}

float Sample::getV(){
	return v;
}

void Sample::print(){
	printf("Sample has pixel (%d, %d) and coordinates (%f, %f)\n", i, j, u, v);
}